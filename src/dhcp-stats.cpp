/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  dhcp-stats.cpp
 * @brief Main file of the project
 * @date  09.11.2023
 */

#include <iostream>
#include <syslog.h>
#include "../include/structs.h"
#include "../include/ncurses_utils.h"
#include "../include/argument_parser.h"
#include "../include/pcap_process.h"
#include "../include/live_capture.h"
#include "../include/print_options.h"

int main(int argc, char *argv[]) {
    Options options = parseArguments(argc, argv);

    openlog("dhcp-stats", LOG_PID, LOG_USER);

    if (!(options.interface.empty())) {
        initNcurses();

        for (const auto &prefix : options.prefixes) {
            PrefixStats newStats;
            newStats.prefix = prefix;
            newStats.maxHosts = calculateMaxHosts(prefix);
            newStats.allocatedAddresses = 0;
            newStats.utilization = 0.0;
            options.prefixStatistics[prefix] = newStats;
        }

        captureLivePackets(options.interface, options.prefixes, options);

        endNcurses();
    } else if (!(options.filename.empty())) {
        processPcapngFile(options.filename, options.prefixes, options);
    }

    printOptions(options);

    for (const auto &pair : options.prefixStatistics) {
        if (pair.second.utilization > 50.0) {
            std::cout << "prefix " << pair.second.prefix << " exceeded 50% of allocations ." << std::endl;
        }
    }

    closelog();

    return 0;
}
