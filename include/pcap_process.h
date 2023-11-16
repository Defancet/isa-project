/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  pcap_process.h
 * @brief Header file for pcap_process.cpp
 * @date  11.11.2023
 */
#ifndef ISA_PROJECT_PCAP_PROCESS_H
#define ISA_PROJECT_PCAP_PROCESS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "pcap/pcap.h"
#include "structs.h"
#include "ncurses_utils.h"
#include "packet_process.h"

/**
 * @brief Processes a pcapng file to monitor DHCP communication.
 * @param filename The name of the pcapng file to be processed.
 * @param prefixes The DHCP prefixes to be monitored.
 * @param options  The program options.
 */
void processPcapngFile(const std::string &filename, const std::vector<std::string> &prefixes,
                       Options &options);

#endif //ISA_PROJECT_PCAP_PROCESS_H
