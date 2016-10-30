default: kernel.iso

AS=x86_64-elf-as
CXX=x86_64-elf-g++
OBJCOPY=x86_64-elf-objcopy

CXXFLAGS_16=-march=i386 -m32 -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-sse4 -mno-sse4.1 -mno-sse4.2
CXXFLAGS=-ffreestanding -std=c++14 -O2 -fno-exceptions -fno-rtti -fno-pic -Wall -Wextra -Werror

multiboot_header.o: multiboot_header.s
	$(AS) -o $@ $^

setup_stack.o: setup_stack.s
	$(AS) -o $@ $^

setup_cpu.o: setup_cpu.cpp
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_16) -c -o $@ $^

setup_cpu_64.o: setup_cpu.o
	$(OBJCOPY) -I elf32-i386 -O elf64-x86-64 $^ $@

kernel.bin: multiboot_header.o setup_stack.o setup_cpu_64.o kernel.o
	$(CXX) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^ -lgcc

kernel.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp $^ isodir/boot/$^
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o $@ isodir

all: kernel.iso

run: all
	qemu-system-x86_64 -cdrom kernel.iso

clean:
	rm *.o
	rm *.bin
	rm *.iso
	rm -r isodir
