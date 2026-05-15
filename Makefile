# Makefile for CPongC - Pong clone in C with SDL3

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wfatal-errors -O3

# Output directory
BINDIR = bin/Debug
TARGET = $(BINDIR)/pong

# Source files - currently only main.c in root
SRCS = main.c display.c

# For the full game (uncomment and add source files as they're moved from old/)
# SRCS = main.c ball.c player.c text.c utils.c audio.c display.c sprite.c main_menu.c

# Object files
OBJS = $(SRCS:.c=.o)

# SDL3 flags
SDL_CFLAGS := $(shell pkg-config --cflags sdl3 2>/dev/null)
SDL_LIBS := $(shell pkg-config --libs sdl3 2>/dev/null)
SDL_LIBS += -lSDL3_image -lSDL3_sound

# Final flags
CFLAGS += $(SDL_CFLAGS)
LDFLAGS = $(SDL_LIBS)

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$<

.PHONY: all clean rebuild run
