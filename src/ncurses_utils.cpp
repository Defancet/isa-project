/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  ncurses_utils.cpp
 * @brief Implementation of functions for ncurses-based user interface
 * @date  15.11.2023
 */

#include "../include/ncurses_utils.h"

WINDOW *win;

void initNcurses() {
    initscr();
    clear();
    noecho();
    cbreak();
    refresh();
    win = newwin(10, 100, 0, 0);
    wrefresh(win);
}

void endNcurses() {
    endwin();
}

void updateNcurses(const Options &options) {
    werase(win);
    mvwprintw(win, 0, 0, "IP-Prefix Max-hosts Allocated addresses Utilization");
    int row = 1;

    std::vector<std::pair<std::string, double>> sortedPrefixes;

    for (const auto &pair: options.prefixStatistics) {
        sortedPrefixes.emplace_back(pair.first, pair.second.utilization);
    }

    for (const auto &prefix: options.prefixes) {
        auto it = options.prefixStatistics.find(prefix);
        if (it == options.prefixStatistics.end()) {
            sortedPrefixes.emplace_back(prefix, 0.0);
        }
    }

    std::sort(sortedPrefixes.begin(), sortedPrefixes.end(),
              [](const auto &a, const auto &b) { return b.second < a.second; });

    for (const auto &pair: sortedPrefixes) {
        auto it = options.prefixStatistics.find(pair.first);
        if (it != options.prefixStatistics.end()) {
            mvwprintw(win, row, 0, "%s %u %u %.2f%%", it->second.prefix.c_str(), it->second.maxHosts,
                      it->second.allocatedAddresses, it->second.utilization);

            row++;
        }
    }

    for (const auto &pair : sortedPrefixes) {
        auto it = options.prefixStatistics.find(pair.first);
        if (it != options.prefixStatistics.end() && it->second.utilization >= 50.0) {
            mvwprintw(win, row, 0, "Prefix %s exceeded 50%% of allocations .",
                      it->second.prefix.c_str());
        }
        row++;
    }

    wrefresh(win);
}
