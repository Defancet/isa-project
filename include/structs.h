/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  structs.h
 * @brief Header file defining data structures
 * @date  09.11.2023
 */

#ifndef ISA_PROJECT_STRUCTS_H
#define ISA_PROJECT_STRUCTS_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Structure to store statistics for a DHCP prefix.
 */
struct PrefixStats {
    std::string prefix;
    uint32_t maxHosts;
    uint32_t allocatedAddresses;
    double utilization;
};

/**
 * @brief Structure to store command-line options for the program.
 */
struct Options {
    std::string interface;
    std::string filename;
    std::vector<std::string> prefixes;
    std::map<std::string, PrefixStats> prefixStatistics;
};

/**
 * @brief Structure to hold user-specific data for DHCP monitoring
 */
struct UserData {
    std::vector<std::string> prefixes;
    Options options;
};

#endif //ISA_PROJECT_STRUCTS_H
