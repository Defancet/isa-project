/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  live_capture.cpp
 * @brief Implementation of live packet capture functionality
 * @date  14.11.2023
 */

#include "../include/live_capture.h"

void captureLivePackets(const std::string &interface, const std::vector<std::string> &prefixes,
                        Options &options) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Error opening live capture on interface " << interface << ": " << errbuf
                  << std::endl;
        exit(EXIT_FAILURE);
    }

    struct pcap_pkthdr header;
    const u_char *packet;

    signal(SIGINT, handleSignal);

    while (!interrupted) {
        packet = pcap_next(handle, &header);

        if (packet != nullptr) {
            processPacket(packet, prefixes, options);
            updateNcurses(options);
        }
    }

    pcap_close(handle);
}
