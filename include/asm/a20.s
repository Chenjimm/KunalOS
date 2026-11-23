[bits 16]

enable_a20:
	call check_a20_start
	cmp ax, 0
	je enable_a20_success

	call fast_a20
	call check_a20_start
	cmp ax, 0
	je enable_a20_success

	call int_a20
	call check_a20_start
	cmp ax, 0
	je enable_a20_success

	call keyboard_a20
	call check_a20_start
	cmp ax, 0
	je enable_a20_success

	mov ax, 1
	ret

enable_a20_success:
	mov ax, 0
	ret

keyboard_a20:
	cli

	call wait_input

	mov al, 0xad ; disable keyboard
	out 0x64, al

	call wait_input

	mov al, 0xd0
	out 0x64, al

	call wait_output

	in al, 0x60
	push ax

	call    wait_input

    mov     al,0xD1
    out     0x64,al         ; write next byte into controller output port

	call    wait_input

    pop     ax
    or      al,2            ; set controller output bit for A20 on
    out     0x60,al         ; activate A20

	call    wait_input

    mov     al,0xAE
    out     0x64,al         ; reactivate keyboard

	call    wait_input

    sti                     ; reactivate interrupts
    ret

wait_input:
	in al, 0x64
	test al, 2
	jnz wait_input
	ret

wait_output:
	in al, 0x64
	test al, 1
	jz wait_output
	ret

int_a20:
	mov ax, 0x2401
	int 0x15
	ret

fast_a20:
	in  al, 0x92
	test al, 2          ; 检查 A20 是否已开启
	jnz fastdone
	or  al, 2           ; 开启 Bit 1 (A20)
	and al, 0xFE        ; 确保 Bit 0 (快速复位) 为 0
	out 0x92, al
fastdone:
	ret

; Use the wrap-around mechanism to check whether the A20 bus is enabled.
; a20 is not enable if ax = 1
check_a20_start:
	pushf
    push ds
    push es
    push di
    push si
	
	cli

	xor ax, ax
	mov es, ax

	not ax
	mov ds, ax

	mov di, 0x0500
	mov si, 0x0510

	mov al, byte[es:di]
	push ax

	mov al, byte[ds:si]
	push ax

	mov byte[es:di], 0x00
	mov byte[ds:si], 0xff

	cmp byte[es:di], 0xff

	pop ax
	mov byte[ds:si], al

	pop ax
	mov byte[es:di], al
	
	mov ax, 1
	je check_a20_end

	mov ax, 0

check_a20_end:
	pop si
    pop di
    pop es
    pop ds
    popf

	ret
