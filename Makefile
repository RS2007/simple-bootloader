all: compile

compile: boot32bit.S
	nasm -f elf32 boot32bit.S -o boot.o
	clang-13 -o boot.bin -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra -Werror -T linker.ld hello.c boot.o -m32
qemu: boot.bin
	qemu-system-x86_64 -curses -fda ./boot.bin -s 
