/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  packet_process.h
 * @brief Header file for packet_process.cpp
 * @date  11.11.2023
 */

#ifndef ISA_PROJECT_PACKET_PROCESS_H
#define ISA_PROJECT_PACKET_PROCESS_H

#include <pcap/pcap.h>
#include <cstring>
#include <algorithm>
#include "structs.h"
#include "ncurses_utils.h"
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/ether.h>
#include <syslog.h>
#include <vector>
#include <stdexcept>
#include <iostream>

/**
 * @brief Calculate the maximum number of hosts for a given DHCP prefix.
 * @param prefix DHCP prefix string.
 * @return Maximum number of hosts for the prefix.
 */
uint32_t calculateMaxHosts(const std::string &prefix);

/**
 * @brief Update DHCP prefix statistics based on allocated addresses.
 * @param prefix             DHCP prefix string.
 * @param allocatedAddresses Number of allocated IP addresses for the prefix.
 * @param options            The program options.
 */
void updateStats(const std::string &prefix, uint32_t allocatedAddresses, Options &options);

/**
 * @brief Process a network packet and update DHCP prefix statistics.
 * @param packet   Pointer to the network packet.
 * @param prefixes List of DHCP prefixes to monitor.
 * @param options  The program options.
 */
void processPacket(const u_char *packet, const std::vector<std::string> &prefixes, Options &options);

/**
 * @brief Callback function for handling network packets.
 *
 * @param userData User-specific data for DHCP monitoring.
 * @param pkthdr   Packet header information.
 * @param packet   Pointer to the network packet.
 */
void packetHandler(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);

#endif //ISA_PROJECT_PACKET_PROCESS_H
