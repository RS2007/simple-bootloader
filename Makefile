all: compile

compile: boot32bit.S
	nasm -f bin boot32bit.S -o boot.bin

qemu: boot.bin
	qemu-system-x86_64 -curses -fda ./boot.bin
