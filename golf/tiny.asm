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
		dd	1
_start:	jmp nxt+1
nxt:    
        jmp 0x1EC0BE7
        jmp 0x1EC01F3
        jmp 0x9009E402
        jmp an+1
an:
        jmp 0x1EC20fb
        jmp 0x9091811a

  
filesize	equ	$ - $$