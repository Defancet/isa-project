/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  ncurses_utils.h
 * @brief Header file for ncurses_utils.cpp
 * @date  15.11.2023
 */

#ifndef ISA_PROJECT_NCURSES_UTILS_H
#define ISA_PROJECT_NCURSES_UTILS_H

#include <ncurses.h>
#include <algorithm>
#include "structs.h"

extern WINDOW *win;

/**
 * @brief Initialize the Ncurses library.
 */
void initNcurses();


/**
 * @brief Clean up and close the Ncurses library.
 */
void endNcurses();

/**
 * @brief Update the Ncurses window with DHCP statistics.
 * @param options The program options.
 */
void updateNcurses(const Options &options);

#endif // ISA_PROJECT_NCURSES_UTILS_H
