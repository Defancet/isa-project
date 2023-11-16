/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  signal_handler.cpp
 * @brief Signal handler implementation
 * @date  14.11.2023
 */

#include "../include/signal_handler.h"
#include "../include/ncurses_utils.h"

bool interrupted = false;

void handleSignal(int signo) {
    if (signo == SIGINT) {
        interrupted = true;
        endNcurses();
        exit(signo);
    }
}
