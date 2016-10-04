
hello.bin:
	as hello.S -o hello.o
	#-Ttext 0x7c00: tells the linker that the text/code segment will be loaded at 0x7c00
	#--oformat binary: plain binary output (no headers, no startup code, _start symbol mapped at the beginning of the file)
	ld -Ttext 0x7c00 --oformat binary hello.o -o hello.bin

run_hello: hello.bin
	#note: qemu-system-x86_64 would also work because both architecture boot in real mode (16 bit)
	qemu-system-i386 -fda hello.bin

clean:
	rm hello.o hello.bin
