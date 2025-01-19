CA ?= langtons_ant

CFLAGS  += $(shell pkg-config --cflags sdl3) -g -O2 -Wall -Werror -Wextra -Wpedantic
LDFLAGS += $(shell pkg-config --libs sdl3)

compile:
	mkdir -p ./build

	$(CC) $(CFLAGS) -c ./src/platform_sdl3.c     -o ./build/sdl3.o
	$(CC) $(CFLAGS) -c ./src/platform_terminal.c -o ./build/terminal.o

	$(CC) $(CFLAGS) ./build/sdl3.o ./src/rule110.c      -o ./build/rule110      $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/wireworld.c    -o ./build/wireworld    $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/langtons_ant.c -o ./build/langtons_ant $(LDFLAGS)

run:
	./build/$(CA)
