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
_start:	jmp nxt+1
nxt:    
        jmp 0x1B80BE5
        jmp ab+1
ab:
        jmp 0x9009E3FD
        jmp ac+1
ac:
        jmp 0x80CE20F6
  
filesize	equ	$ - $$