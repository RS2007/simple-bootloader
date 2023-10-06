all: compile

compile: boot32bit.S
	nasm -f elf32 boot32bit.S -o boot.o
	clang-13 -o boot.bin -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -Wall -Wextra  -T linker.ld vga_driver.c hello.c boot.o -m32
qemu: compile
	qemu-system-x86_64  -fda ./boot.bin -s -curses
