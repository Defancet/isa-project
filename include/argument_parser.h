/**
 * ISA Project – Monitoring DHCP communication
 * @author
 *   xkalut00, Maksim Kalutski
 *
 * @file  argument_parser.h
 * @brief Header file for argument_parser.cpp
 * @date  09.11.2023
 */

#ifndef ISA_PROJECT_ARGUMENT_PARSER_H
#define ISA_PROJECT_ARGUMENT_PARSER_H

#include <iostream>
#include <cstring>
#include <getopt.h>
#include <stdexcept>
#include "../include/structs.h"

/**
 * @brief Prints usage of the program.
 * @param programName name of the program
 */
void printUsage(const char *programName);

/**
 * @briefParses arguments from command line
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return Options struct with parsed arguments
 */
Options parseArguments(int argc, char *argv[]);

#endif //ISA_PROJECT_ARGUMENT_PARSER_H
