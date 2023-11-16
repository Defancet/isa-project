cmake_minimum_required(VERSION 3.22)
project(isa_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(isa_project  src/dhcp-stats.cpp
        src/signal_handler.cpp
        src/print_options.cpp
        src/pcap_process.cpp
        src/packet_process.cpp
        src/ncurses_utils.cpp
        src/live_capture.cpp
        src/dhcp-stats.cpp
        src/argument_parser.cpp
        include/structs.h
        include/signal_handler.h
        include/print_options.h
        include/pcap_process.h
        include/packet_process.h
        include/ncurses_utils.h
        include/live_capture.h
        include/argument_parser.h
)
