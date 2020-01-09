# $^ is substituted with all the dependencies
# $< is the first dependency
# $@ is the target

# This expands to a list of files which match the pattern
C_SRC_FILES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SRC_FILES:.c=.o}

all: os_image

run: all
	bochs

os_image: boot/boot_sector.bin kernel.bin
	cat $^ > os_image

kernel.bin: kernel/kernel_entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 --oformat binary $^

clean:
	rm -fr *.bin *.dis *.o os_image *.map
	rm -fr kernel/*.o drivers/*.o

kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@


%.o: %.c ${HEADERS}
	i386-elf-gcc -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@