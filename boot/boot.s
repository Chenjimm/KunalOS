[bits 16]

global start
section .boot

start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, ax

	mov bx, hello_string
	call print_start

load_disk:
	mov si, dap
	mov ah, 0x42
	mov dl, 0x80
	int 0x13
	jc error
	jmp 0x07e0:0x0000

dap:
	db 0x10
	db 0x00
	dw 126
	dw 0x0000
	dw 0x07e0
	dq 0x0000000000000001

disk:
	db 1

error:
	hlt

hello_string:
	db "Hello, KunalOS!", 0x0d, 0x0a, "loading disk...", 0x0d, 0x0a, 0

%include "../include/asm/print.s"

times 510-($-$$) db 0
dw 0xaa55
