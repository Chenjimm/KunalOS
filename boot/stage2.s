[bits 16]

global stage2_start
section .stage2

stage2_start:
	mov bx, load_success_string
	call print_start

; enable a20 address line
	call enable_a20
	cmp ax, 1
	je a20_fail
	mov bx, a20_success
	call print_start
	jmp $

; build GDT

a20_fail:
	mov bx, a20_fail_string
	call print_start
	jmp $

load_success_string:
	db "Loaded successfully", 0x0d, 0x0a, 0

a20_success:
	db "a20 enable", 0x0d, 0x0a, 0

a20_fail_string:
	db "a20 fail", 0x0d, 0x0a, 0

%include "../include/asm/print.s"
%include "../include/asm/a20.s"
