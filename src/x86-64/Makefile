default: kernel.iso

AS=x86_64-elf-as
CXX=x86_64-elf-g++
CXXFLAGS=-ffreestanding -std=c++14 -O2 -Wall -Wextra -fno-exceptions -fno-rtti

multiboot_header.o: multiboot_header.s
	$(AS) -o $@ $^

boot.o: boot.s
	$(AS) -o $@ $^

kernel.bin: multiboot_header.o boot.o kernel.o
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
