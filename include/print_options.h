/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  print_options.h
 * @brief Header file for print_options.cpp
 * @date  11.11.2023
 */

#ifndef ISA_PROJECT_PRINT_OPTIONS_H
#define ISA_PROJECT_PRINT_OPTIONS_H

#include <iostream>
#include <algorithm>
#include "structs.h"

/**
 * @brief Display IP prefixes, maximum hosts, allocated addresses, and utilization percentage for each prefix.
 * @param options The program options.
 */
void displayPrefixStats(const PrefixStats &stats);


/**
 * @brief Print DHCP monitoring options.
 * @param options The program options.
 */
void printOptions(const Options &options);

#endif //ISA_PROJECT_PRINT_OPTIONS_H
