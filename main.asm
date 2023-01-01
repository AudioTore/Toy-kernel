[org 0x7c00]
KERNEL_LOCATION equ 0x1000

[org 0x7c00]
mov [BootDNum], dl

; Print "Booting..."

; B
mov ah, 0x0e
mov al, 'B'
int 0x10

; o
mov ah, 0x0e
mov al, 'o'
int 0x10

; o
mov ah, 0x0e
mov al, 'o'
int 0x10

; t
mov ah, 0x0e
mov al, 't'
int 0x10

; i
mov ah, 0x0e
mov al, 'i'
int 0x10

; n
mov ah, 0x0e
mov al, 'n'
int 0x10

; g
mov ah, 0x0e
mov al, 'g'
int 0x10

; .
mov ah, 0x0e
mov al, '.'
int 0x10

; .
mov ah, 0x0e
mov al, '.'
int 0x10

; .
mov ah, 0x0e
mov al, '.'
int 0x10

; Video memory configuration..
xor ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, 0x7e00

mov ah, 2
mov al, 1 ; Sectors we want to read.
mov ch, 0 ; Cylindar number.
mov dh, 0 ; Head number.
mov cl, 2 ; Total amount of sectors.
mov dl, [BootDNum]
int 0x13

mov bx, KERNEL_LOCATION
mov dh, 20

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BootDNum]
int 0x13

; Switch to text mode.

mov ah, 0x0
mov al, 0x3
int 0x10

CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp CODE_SEG:start_protected_mode

jmp $

BootDNum: db 0


; Switch to 32 bit protected mode.

GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:


GDT_descriptor:
	dw GDT_end - GDT_start - 1
	dd GDT_start

[bits 32]
start_protected_mode:
   mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp
		
	
  jmp KERNEL_LOCATION

times 510-($-$$) db 0
db 0x55, 0xaa
