[bits 16]

print_start:
	pushf
    pusha

	mov si, bx

print_loop:
	mov ah, 0x0e
	mov al, [si]
	cmp al, 0
	je end
	int 0x10
	add si, 1
	jmp print_loop

end:
	popa
	popf
	ret
