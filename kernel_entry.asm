global _start
_start:
	[bits 32]
	[extern main]
	call main
	jmp $
