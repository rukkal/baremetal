.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.code32
.global _start
.type _start, @function

_start:
	mov $stack_top, %esp
	call setup_cpu

.size _start, . - _start
