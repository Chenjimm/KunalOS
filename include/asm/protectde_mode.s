; 1. disable interrupts
; 2. load gdt
; 3. cr0 -> 1
; 4. jmp init protected mode
; 5. set the registers

[bits 16]
SwitchToProtectedMode:
	cli
	lgdt [GDTDescriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEL:InitProtectedMode

[bits 32]

InitProtectedMode:
	mov ax, DATA_SEL
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call BeginProtectedMode
