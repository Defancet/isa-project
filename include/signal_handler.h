/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  signal_handler.h
 * @brief Header file for signal_handler.cpp
 * @date  14.11.2023
 */

#ifndef ISA_PROJECT_SIGNAL_HANDLER_H
#define ISA_PROJECT_SIGNAL_HANDLER_H

#include <csignal>
#include <cstdlib>

extern bool interrupted;

/**
 * @brief Handles the interrupt signal (SIGINT)
 * @param signo Signal number
 */
void handleSignal(int signo);

#endif // ISA_PROJECT_SIGNAL_HANDLER_H
