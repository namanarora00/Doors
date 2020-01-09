# $^ is substituted with all the dependencies
# $< is the first dependency
# $@ is the target

all: os_image

run: all
	bochs

os_image: boot_sector.bin kernel.bin
	cat boot_sector.bin kernel.bin > os_image

kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

kernel_entry.o: kernel_entry.asm
	nasm kernel_entry.asm -f elf -o kernel_entry.o

boot_sector.bin: boot_sector.asm
	nasm $< -f bin -o $@

# kernel.o and kernel_entry.o are dependencies of kernel.bin.
# so make kernel.bin will first make kernel.o and kernel_entry.o
kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 --oformat binary $^

clean:
	rm -fr *.bin *.dis *.o os_image *.map

kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@