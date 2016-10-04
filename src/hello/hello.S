
.code16
.section .text
.global _start

_start:
    movb $'h' , %al
    movb $0x0e, %ah
    int  $0x10

    movb $'i' , %al
    movb $0x0e, %ah
    int  $0x10
    
    movb $' ' , %al
    movb $0x0e, %ah
    int  $0x10
    
    movb $'k' , %al
    movb $0x0e, %ah
    int  $0x10
    
    movb $'e' , %al
    movb $0x0e, %ah
    int  $0x10
    
    movb $'a' , %al
    movb $0x0e, %ah
    int  $0x10
    
    movb $'n' , %al
    movb $0x0e, %ah
    int  $0x10
    
    #boot signature at bytes 510 and 511 (total length 512B)
    . = _start + 510 
    .byte 0x55
    .byte 0xaa 
