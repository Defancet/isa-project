/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  print_options.cpp
 * @brief Implementation file for functions related to printing options.
 * @date  11.11.2023
 */

#include "../include/print_options.h"

void displayPrefixStats(const PrefixStats &stats) {
    printf("%s %u %u %.2f%%\n", stats.prefix.c_str(), stats.maxHosts, stats.allocatedAddresses,
           stats.utilization);
}

void printOptions(const Options &options) {
    std::cout << "IP-Prefix Max-hosts Allocated addresses Utilization\n";

    std::vector<std::pair<std::string, double>> sortedPrefixes;

    for (const auto &pair: options.prefixStatistics) {
        sortedPrefixes.emplace_back(pair.first, pair.second.utilization);
    }

    std::sort(sortedPrefixes.begin(), sortedPrefixes.end(),
              [](const auto &a, const auto &b) { return b.second < a.second; });

    for (const auto &pair: sortedPrefixes) {
        auto it = options.prefixStatistics.find(pair.first);
        if (it != options.prefixStatistics.end()) {
            displayPrefixStats(it->second);
        }
    }
}
