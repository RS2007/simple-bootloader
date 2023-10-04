bits 16
org 0x7c00 ; outputs stuff at offset, and bios will start executing here

boot:
  mov si,hello ; there is an instruction to load the string at si to the al register thus we can use a reference to the string, alternative is to load each byte to al and then print it using the interrupt
  mov ah,0x0e ; interrupt number loaded to the ah register

.loop:
  lodsb ; loads the byte at memory si to al(special instruction)
  or al,al ; or is used to check whether al is 0
  jz halt
  int 0x10
  jmp .loop

halt:
  cli ; clear interrupt flag
  hlt ; halt execution
  



hello: db "Hello, World!",0 ; db is technically one byte, but when given multiple bytes it writes them one byte at a time contigously

times 510 - ($ - $$) db 0 ; pad remaining 510 bytes with 0
dw 0xaa55 ; magic bootloader number to make it bootable


