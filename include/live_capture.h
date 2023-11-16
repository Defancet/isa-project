/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  live_capture.h
 * @brief Header file for live_capture.cpp
 * @date  14.11.2023
 */

#ifndef ISA_PROJECT_LIVE_CAPTURE_H
#define ISA_PROJECT_LIVE_CAPTURE_H

#include <iostream>
#include <csignal>
#include <pcap/pcap.h>
#include "structs.h"
#include "ncurses_utils.h"
#include "packet_process.h"
#include "signal_handler.h"

/**
 * @brief Captures live packets on given interface and processes them
 * @param interface Interface to capture packets on
 * @param prefixes  Prefixes to filter packets by
 * @param options   The program options.
 */
void captureLivePackets(const std::string &interface, const std::vector<std::string> &prefixes,
                        Options &options);

#endif //ISA_PROJECT_LIVE_CAPTURE_H
