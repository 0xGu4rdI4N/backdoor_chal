BITS 32
  
		org	0x00010000
  
		db	0x7F, "ELF"
		dd	1
		dd	0
		dd	$$
		dw	2
		dw	3
		dd	_start
		dd	_start
		dd	4
        bin_sh:	db	"/bin/sh", 0
		dw	0x34
		dw	0x20
		dw	1
_start:	mov	al,	11
        mov	ebx,	bin_sh
        int	0x80
		jmp _start
		jmp _start
		jmp _start
		jmp _start
		jmp _start
		jmp _start

  
filesize	equ	$ - $$