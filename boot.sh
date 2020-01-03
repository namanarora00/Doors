# assembler and simulator commands
nasm boot_sector.asm -f bin -o boot_sector.bin

# Creates the object file
/usr/local/i386elfgcc/bin/i386-elf-gcc -ffreestanding -c kernel.c -o kernel.o

# Linker. Creates the binary file from object file. Also we tell the linker that the origin of the code once loaded is at 0x1000.
# Like [org 0x7c00].
/usr/local/i386elfgcc/bin/i386-elf-ld -o kernel.bin -Ttext 0x1000 --oformat binary kernel.o

# Concatenates the boot sector code and kernel code so that we can load them using a single floppy(boot disk).
# This way we know the sectors containing different code.
cat boot_sector.bin kernel.bin > os_image

# start simulation
bochs