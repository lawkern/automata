compile:
	mkdir -p ./build
	$(CC) -g ./src/rule110.c -o ./build/rule110

run:
	./build/rule110
