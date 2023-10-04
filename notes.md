# Notes

- for booting an os, we need to put the booting related code at the place where the bios will start executing code, thus the instructions are put at `0x7c00`
- next the hello world string is stored at the end of the memory post the instructions
- the rest of the memory from the place where we stored hello world string(end of instructions) is written to 0. This is done till the 510th bit from the start of the section. The last 2 bits are written as `0xaa55` which marks it as a bootable.
- the si register stores the string "hello world" and the bios interrupt to write to vga(`0x0e`) is written to lower part of the `ax` register (`al`). At the higher part of the 

> The instruction `lodsb` is extremely weird. It loads the byte from memory location mentioned in the `si` register into the `al` register and then increments or decrements the `esi` register based on the direction flag in `eflags` register. The direction flag is default set to 0 and hence `si` will be incremented. Now `si` will point to the character `e`(hello_pointer + 1)


- On boot the cpu is in real mode:([Processor modes](https://flint.cs.yale.edu/feng/cos/resources/BIOS/procModes.htmh))
  - In real mode, you can only access 1 MiB of memory, can only call bios interrupts and use 16 bit instructions
  - In order to access more than the limit, OS developers need to enable the `A20 line` using the `A20 gate activate function`.([Reference](https://wiki.osdev.org/A20_Line))
  - Different ways of enabling the `A20 gate` and some hardware details about it([here](https://mrhopehub.github.io/2014/12/26/enabling-the-A20-Gate.html)). From the article to enable the gate one needs to set `ax` to `0x2401` and call bios memory interrupt `0x15` 
  - Info on VGA Text mode 3 as the most common way of memory mapping to VGA([here](https://wiki.osdev.org/Text_UI))


## Shifting to 32 bit
- Initially we start in 16 bit mode at the location `0x7c00`
- Once the `A20 line` is activated and vga text mode is turned to 3, the gdt is loaded using `lgdt` instruction
- memory can be accessed technically now, but how does the processor know(HINT: change the control register)
- Control register `cr0` is set to `0x1`:  
  1. move the value to `eax`
  2. bitwise or with `0x1` 
  3. then move eax to cr0
- Now the processor knows we are in `32 bit protected mode`
- Relative jump to the setup label in the code segment(`CODE_SEG:setup`)

## Global descriptor table
- binary data structure corresponding to the Intel 32 bit and x86 64 bit architectures.
- Tells cpu about memory segments(ELF file lite?)
- GDT is pointed to via the `GDTR` register and is loaded via the `LGDT` assembly instruction whose argument is a pointer to this structure.
- GDT starts of with a null descriptor(a quad word is set to 0 for the same)
- For the structure of each gdt entry refer to this [url](https://wiki.osdev.org/GDT)
- At the end of gdt we have a descriptor with the size of the gdt and a pointer to the start of the gdt
