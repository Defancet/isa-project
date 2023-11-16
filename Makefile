CC = g++
CFLAGS = -Wall -Wextra -g
LFLAGS = -lpcap -lncurses
SRC_DIR = src
INCLUDE_DIR = include
EXEC = dhcp-stats

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ -I$(INCLUDE_DIR) $(LFLAGS)

clean:
	rm -f $(EXEC)
