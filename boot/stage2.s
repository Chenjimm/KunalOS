[bits 16]

global stage2_start
section .stage2

stage2_start:
	mov si, load_success

print_loop:
	mov ah, 0x0e
	mov al, [si]
	cmp al, 0
	je end
	int 0x10
	add si, 1
	jmp print_loop

end:

load_success:
	db "Loaded successfully", 0x0d, 0x0a, 0
