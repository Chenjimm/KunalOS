[bits 16]

global start
section .boot

start:
	xor ax, ax
	mov ds, ax
	mov es, ax
	mov ss, ax

	mov si, hello_string

print_loop:
	mov ah, 0x0e
	mov al, [si]
	cmp al, 0
	je load_disk
	int 0x10
	add si, 1
	jmp print_loop

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
	dw 64
	dw 0x0000
	dw 0x07e0
	dq 0x0000000000000001

disk:
	db 1

error:
	hlt

hello_string:
	db "Hello, OS!", 0x0d, 0x0a, "loading disk...", 0x0d, 0x0a, 0

times 510-($-$$) db 0
dw 0xaa55
