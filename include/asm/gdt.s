; Segment:
	; A logically contiguoues chunk of memory with consistent properties
; Segment Register:
	; A register of your CPU that refers to a segment for a particular purpose(CS, DS, ES, SS) of for general use(FS, GS)
; Segment Selector:
	; A reference to a descriptor, which you can load into a segment register; the selector is an offset into a descriptor table pointing to one of its entries. These entries are typically 8 bytes long, therefore bits 3 and up only declare the descriptor table entry offset, while bit 2 specifies if this selector is a GDT or LDT selector (LDT - bit set, GDT - bit cleared), and bits 0 - 1 declare the ring level that needs to correspond to the descriptor table entry's DPL field. If it doesn't, a General Protection Fault occurs; if it does correspond then the CPL level of the selector used is changed accordingly.
; Segment Descriptor:
	; A entry of the GDT.

; A Basic GDT should have these entry:
	; A NULL ertry
	; A DPL 0 Code Segment descriptor (for kernal)
	; A Data Segment descriptor (Code Segment should not change it)
	; A Task Stage Segment segment descriptor

; for each Descriptor, there are 8bytes (64bits)

GDTStart:
	dd 0x0
	dd 0x0

GDTKernalModeCodeSegment:
	dw 0xFFFF ; limit
	dw 0x0000 ; Base
	
	db 0x00 ; Base
	db 0x9A ; Access Byte
	db 0xCF ; Flag and Limit
	db 0x00 ; Base

GDTKernalModeDataSegment:
	dw 0xFFFF ; limit
	dw 0x0000 ; Base
	
	db 0x00 ; Base
	db 0x92 ; Access Byte
	db 0xCF ; Flag and Limit
	db 0x00 ; Base

GDTUserModeCodeSegment:
	dw 0xFFFF ; limit
	dw 0x0000 ; Base
	
	db 0x00 ; Base
	db 0xFA ; Access Byte
	db 0xCF ; Flag and Limit
	db 0x00 ; Base

GDTUserModeDataSegment:
	dw 0xFFFF ; limit
	dw 0x0000 ; Base
	
	db 0x00 ; Base
	db 0xF2 ; Access Byte
	db 0xCF ; Flag and Limit
	db 0x00 ; Base

GDTEnd:

GDTDescriptor:
	dw GDTEnd - GDTStart - 1 ; limit
	dd GDTStart ; base

CodeSelector:
	CODE_SEL equ GDTKernalModeCodeSegment - GDTStart
	DATA_SEL equ GDTKernalModeDataSegment - GDTStart
