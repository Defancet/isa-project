/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  argument_parser.cpp
 * @brief Source file contains the implementation of command-line argument parsing function.
 * @date  09.11.2023
 */

#include "../include/argument_parser.h"

void printUsage(const char *programName) {
    std::cout << "Usage: " << programName
              << " [-r <filename> | -i <interface-name>] <ip-prefix> [ <ip-prefix> [ ... ] ]\n";
    std::cout << "Options:\n";
    std::cout << "  -r <filename> - statistics will be created from pcap files\n";
    std::cout << "  -i <interface> - interface on which the program can listen\n\n";
}

Options parseArguments(int argc, char *argv[]) {
    Options options;
    int opt;
    bool hasInterface = false;
    bool hasFilename = false;

    while ((opt = getopt(argc, argv, "i:r:")) != -1) {
        switch (opt) {
            case 'i':
                if (hasFilename) {
                    std::cerr << "Error: Cannot use both -i and -r options simultaneously." << std::endl;
                    printUsage(argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                options.interface = optarg;
                hasInterface = true;
                break;
            case 'r':
                if (hasInterface) {
                    std::cerr << "Error: Cannot use both -i and -r options simultaneously." << std::endl;
                    printUsage(argv[0]);
                    std::exit(EXIT_FAILURE);
                }
                options.filename = optarg;
                hasFilename = true;
                break;
            default:
                printUsage(argv[0]);
                std::exit(EXIT_FAILURE);
        }
    }

    for (int i = optind; i < argc; ++i) {
        options.prefixes.emplace_back(argv[i]);
    }

    if (options.prefixes.empty() || (!hasInterface && !hasFilename)) {
        std::cerr << "Error: At least one IP prefix and either -i or -r option are required." << std::endl;
        printUsage(argv[0]);
        std::exit(EXIT_FAILURE);
    }

    return options;
}
