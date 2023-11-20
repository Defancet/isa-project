/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  pcap_process.cpp
 * @brief Implementation of pcap process function
 * @date  11.11.2023
 */

#include "../include/pcap_process.h"

void processPcapngFile(const std::string &filename, const std::vector<std::string> &prefixes,
                       Options &options) {
    initNcurses();

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    handle = pcap_open_offline(filename.c_str(), errbuf);
    if (handle == nullptr) {
        endNcurses();
        std::cerr << "Error opening pcapng file: " << errbuf << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &prefix: prefixes) {
        if (options.prefixStatistics.find(prefix) == options.prefixStatistics.end()) {
            PrefixStats newStats;
            newStats.prefix = prefix;
            newStats.maxHosts = calculateMaxHosts(prefix);
            newStats.allocatedAddresses = 0;
            newStats.utilization = 0.0;

            options.prefixStatistics[prefix] = newStats;
        }
    }

    UserData userDataStruct;
    userDataStruct.prefixes = prefixes;
    userDataStruct.options = options;

    int loopResult = pcap_loop(handle, 0, packetHandler, reinterpret_cast<u_char *>(&userDataStruct));
    if (loopResult == -1) {
        endNcurses();
        std::cerr << "Error in pcap_loop: " << pcap_geterr(handle) << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &prefix: prefixes) {
        options.prefixStatistics[prefix].allocatedAddresses =
                userDataStruct.options.prefixStatistics[prefix].allocatedAddresses;
        options.prefixStatistics[prefix].utilization =
                (static_cast<double>(options.prefixStatistics[prefix].allocatedAddresses) /
                 options.prefixStatistics[prefix].maxHosts) *
                100;
    }

    pcap_close(handle);

    endNcurses();
}
