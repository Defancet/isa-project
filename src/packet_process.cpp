/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  packet_process.cpp
 * @brief Implementation of packet processing functions
 * @date  11.11.2023
 */

#include "../include/packet_process.h"

uint32_t calculateMaxHosts(const std::string &prefix) {
    size_t pos = prefix.find('/');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid IP prefix format: " + prefix);
    }

    std::string mask = prefix.substr(pos + 1);
    return (1u << (32 - std::stoi(mask))) - 2;
}

void updateStats(const std::string &prefix, uint32_t allocatedAddresses, Options &options) {
    auto it = options.prefixStatistics.find(prefix);
    if (it != options.prefixStatistics.end()) {
        if (it->second.utilization >= 100.0) {
            return;
        }

        it->second.allocatedAddresses += allocatedAddresses;
        it->second.utilization =
                (static_cast<double>(it->second.allocatedAddresses) / it->second.maxHosts) * 100;

        if (it->second.utilization >= 50.0 && it->second.utilization - allocatedAddresses < 50.0) {
            syslog(LOG_WARNING, "prefix %s exceeded 50%% of allocations.", prefix.c_str());
        }
    } else {
        PrefixStats newStats;
        newStats.prefix = prefix;
        newStats.maxHosts = calculateMaxHosts(prefix);
        newStats.allocatedAddresses = allocatedAddresses;
        newStats.utilization = (static_cast<double>(allocatedAddresses) / newStats.maxHosts) * 100;

        if (newStats.utilization >= 50.0) {
            syslog(LOG_WARNING, "prefix %s exceeded 50%% of allocations.", prefix.c_str());
        }

        options.prefixStatistics[prefix] = newStats;
    }
}


void processPacket(const u_char *packet, const std::vector<std::string> &prefixes, Options &options) {
    struct ether_header *eth_header = (struct ether_header *) packet;

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        struct ip *ip_header = (struct ip *) (packet + sizeof(struct ether_header));
        uint32_t src_ip = ntohl(ip_header->ip_src.s_addr);

        if (src_ip == 0 || src_ip == 0xFFFFFFFF) {
            return;
        }

        static std::vector<uint32_t> processedAddresses;
        if (std::find(processedAddresses.begin(), processedAddresses.end(), src_ip) !=
            processedAddresses.end()) {
            return;
        }
        processedAddresses.emplace_back(src_ip);

        for (const auto &prefix: prefixes) {
            size_t pos = prefix.find('/');
            std::string ipPrefix = prefix.substr(0, pos);
            std::string mask = prefix.substr(pos + 1);
            uint32_t prefixMask = (0xFFFFFFFF << (32 - std::stoi(mask))) & 0xFFFFFFFF;
            uint32_t prefixStart = ntohl(inet_addr(ipPrefix.c_str())) & prefixMask;

            if ((src_ip & prefixMask) == prefixStart) {
                updateStats(prefix, 1, options);

                for (const auto &otherPrefix: prefixes) {
                    if (otherPrefix != prefix) {
                        size_t otherPos = otherPrefix.find('/');
                        std::string otherIpPrefix = otherPrefix.substr(0, otherPos);
                        std::string otherMask = otherPrefix.substr(otherPos + 1);
                        uint32_t otherPrefixMask = (0xFFFFFFFF << (32 - std::stoi(otherMask))) & 0xFFFFFFFF;
                        uint32_t otherPrefixStart = ntohl(inet_addr(otherIpPrefix.c_str())) & otherPrefixMask;

                        if ((src_ip & otherPrefixMask) == otherPrefixStart) {
                            updateStats(otherPrefix, 1, options);
                            break;
                        }
                    }
                }

                break;
            }
        }
    }
}

void packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
    UserData *userDataStruct = reinterpret_cast<UserData *>(userData);
    processPacket(packet, userDataStruct->prefixes, userDataStruct->options);
}
