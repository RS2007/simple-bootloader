bits 16
org 0x7c00

boot:
  mov ax,0x2401
  int 0x15 ; enable A20 bit
  mov ax,0x3
  int 0x10 ; set vga text mode to 3
  lgdt [gdt_pointer]
  mov eax,cr0
  or eax,0x1
  mov cr0,eax
  jmp CODE_SEG:setup

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

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
setup: ; data segment address loaded to the segment registers 
  mov ax, DATA_SEG
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov ss, ax
  mov esi,hello ; load hello to the esi register
  mov ebx,0xb8000 ; store the start of the memory map to vga
.loop:
  lodsb
  or al,al
  jz halt
  or eax,0x0100
  mov word [ebx], ax
  add ebx,2
  jmp .loop
halt:
  cli
  hlt
hello: db "Hello world!",0
times 510 - ($-$$) db 0
dw 0xaa55
