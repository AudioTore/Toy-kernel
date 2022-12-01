global isr0
global isr1
global isr31

; Make exception for dividing by zero.
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
	push eax

	mov ax, 0x10
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