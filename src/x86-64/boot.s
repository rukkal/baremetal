.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.code32

_start:
	mov $stack_top, %esp
	call kernel_main
1:	hlt
	jmp 1b

.size _start, . - _start
