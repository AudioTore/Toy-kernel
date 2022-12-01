global _start
_start:
	[bits 32]
	[extern main]
	call main
	jmp $


global isr0
global isr1
global isr31

isr0:
	push byte 0
	push byte 0
	jmp isr_common_stub

isr1:
	push byte 0
	push byte 0
	jmp isr_common_stub

isr12:
	push byte 12
	jmp isr_common_stub

isr31:
	push byte 0
	push byte 31
	jmp isr_common_stub

[extern isr_handler]

isr_common_stub:
	pusha

	mov ax, ds
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	push esp
	call isr_handler
	pop eax

	pop eax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa
	
	add esp, 8
	iret