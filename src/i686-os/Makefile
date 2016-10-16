
CXX=i686-elf-g++
CXXFLAGS=-ffreestanding -std=c++14 -O2 -Wall -Wextra -fno-exceptions -fno-rtti

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

kernel.bin: boot.o kernel.o
	i686-elf-g++ -T linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

kernel.iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/kernel.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o kernel.iso isodir

all: kernel.iso

run: all
	qemu-system-i386 -cdrom kernel.iso

clean:
	rm *.o
	rm *.bin
	rm *.iso
	rm -r isodir
