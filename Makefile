CFLAGS  += $(shell pkg-config --cflags sdl3) -g -O2 -Wall -Werror -Wextra -Wpedantic
LDFLAGS += $(shell pkg-config --libs sdl3)

asm-x64: platform
	nasm -g -felf64 ./src/rule110.asm -o ./build/rule110.o
	$(CC) -no-pie -m64 ./build/sdl3.o ./build/rule110.o -o ./build/rule110 $(LDFLAGS)

asm-arm64: platform
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/rule110.s      -o ./build/rule110      $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/wireworld.s    -o ./build/wireworld    $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/langtons_ant.s -o ./build/langtons_ant $(LDFLAGS)

compile: platform
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/rule110.c      -o ./build/rule110      $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/wireworld.c    -o ./build/wireworld    $(LDFLAGS)
	$(CC) $(CFLAGS) ./build/sdl3.o ./src/langtons_ant.c -o ./build/langtons_ant $(LDFLAGS)

platform:
	mkdir -p ./build
	$(CC) $(CFLAGS) -no-pie -c ./src/platform_sdl3.c     -o ./build/sdl3.o
	$(CC) $(CFLAGS) -no-pie -c ./src/platform_terminal.c -o ./build/terminal.o

run:
	./build/$(CA)
