section .boot
bits 16
global boot
; org 0x7c00 ; commented out since the linker script will take care of this from now on

boot:
  mov ax,0x2401
  int 0x15 ; enable A20 bit
  mov ax,0x3
  int 0x10 ; set vga text mode to 3
  mov [disk],dl ; the bios loads the disk number to dl register on boot, we store the value to memory so that we can use it later
  mov ah,0x02
  mov al,0x6 ; sectors to read
  mov ch,0x0 ; cylinder index
  mov dh,0x0 ; head index
  mov cl, 0x2; sector idx, we are reading the second index
  ;In CHS addressing the sector numbers always start at 1, there is no sector 0,[1] which can lead to confusion since logical sector 
  ;addressing schemes typically start counting with 0, e.g., logical block addressing (LBA), or "relative sector addressing" used in DOS.
  mov dl,[disk]
  mov bx,buffer_start; start of the buffer
  int 0x13; memory service interrupt for the bios
  cli ; disable interrupts from here on since we are gonna use memory mapping and subseqeuntly define interrupts in an IDT
  lgdt [gdt_pointer] ; load the gdt
  mov eax,cr0
  or eax,0x1
  mov cr0,eax ; set the cr0 to 1 signalling 32-bit protected mode
  ; setup segmentation registers
  mov ax, DATA_SEG
  mov ds, ax ; data segment
  mov es, ax ; extended segment
  mov fs, ax ;
  mov gs, ax ; 
  mov ss, ax ; stack segment
  jmp CODE_SEG:setup ; jump to setup label in the CODE_SEG

  ;; Setting up the global descriptor table
gdt_start:
  dq 0x0 ; load 8 bits of 0 (null descriptor in the GDT)
gdt_code:
  dw 0xFFFF ; first 16 bits of limit
  dw 0x0000 ; first 24 bits of base
  db 0x00 ; ""
  db 10011010b 
  db 11001111b
  db 0
gdt_data:
  dw 0xFFFF ; first 16 bits of limit
  dw 0x0000 ; first 24 bits of base
  db 0x00 ; ""
  db 10010010b 
  db 11001111b
  db 0
gdt_end:
gdt_pointer:
  dw gdt_end - gdt_start
  dd gdt_start

disk:
  db 0x0

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510 - ($-$$) db 0
dw 0xaa55

buffer_start:
bits 32
hello: db "Hello world from the other sector",0
setup: ; data segment address loaded to the segment registers 
  mov esi,hello ; load hello to the esi register
  mov ebx,0xb8000 ; store the start of the memory map to ebx
;.loop:
;  lodsb
;  or al,al ; check if the value stored in al is 0
;  jz halt  ; if al is 0 then halt
;  or eax,0x0f00 ; setting the ah bit to 10, black text on blue background(Reference: https://wiki.osdev.org/Text_UI) 
;  mov word [ebx], ax ; move the word (2 bytes from ebx,16 bits) from ax to the memory mapped area for the vga
;  add ebx,2 ; The next address to write to is 2 words away from the original, so add 2 to address in ebx
;  jmp .loop
halt:
  mov esp,top_of_stack ; grows downwards so initialize on the top
  extern my_main ; symbol not in current .o file
  call my_main ; call the main function
  cli
  hlt

section .bss:; all variables initialized to 0
align
bottom_of_stack: 
resb 32768 ; reference: https://www.nasm.us/xdoc/2.11.06/html/nasmdoc3.html#section-3.2.2
top_of_stack:
