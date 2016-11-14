default: kernel.iso

AS=x86_64-elf-as
CXX=x86_64-elf-g++
OBJCOPY=x86_64-elf-objcopy

CXXFLAGS_COMMON=-ffreestanding -std=c++14 -O2 -fno-exceptions -fno-rtti -fno-pic -Wall -Wextra -Werror
CXXFLAGS_32=$(CXXFLAGS_COMMON) -march=i386 -m32 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-sse4 -mno-sse4.1 -mno-sse4.2
CXXFLAGS=$(CXXFLAGS_COMMON) -g -mcmodel=small

multiboot_header.o: multiboot_header.s
	$(AS) -o $@ $^

setup_stack.o: setup_stack.s
	$(AS) -o $@ $^

setup_cpu.o: setup_cpu.cpp
	$(CXX) $(CXXFLAGS_32) -c -o $@ $^

setup_cpu_64.o: setup_cpu.o
	$(OBJCOPY) -I elf32-i386 -O elf64-x86-64 $^ $@

kernel.bin: multiboot_header.o setup_stack.o setup_cpu_64.o kernel.o
	$(CXX) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc
	#note: gdb could also load the symbols directly from the original kernel.bin
	#(before performing the following objcopies).
	#However, this approach produces a slimmer kernel file.
	$(OBJCOPY) --only-keep-debug kernel.bin kernel.sym
	$(OBJCOPY) --strip-debug kernel.bin

kernel.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp $^ isodir/boot/$^
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

run: kernel.iso
	qemu-system-x86_64 -cdrom kernel.iso

run_gdb: kernel.iso
	qemu-system-x86_64 -gdb tcp::1234 -S -cdrom kernel.iso

clean:
	rm *.o
	rm *.bin
	rm *.iso
	rm *.sym
	rm -r isodir
