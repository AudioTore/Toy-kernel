export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "main.asm" -f bin -o "main.bin"
nasm "kernel_entry.asm" -f elf -o "kernel_entry.o"
nasm "Drivers/Keyboard/IDT2.asm" -f elf -o "IDT2.o"
i386-elf-gcc -ffreestanding -m32 -g -c "kernel.cpp" -o "kernel.o"
nasm "doublebyte.asm" -f bin -o "doublebyte.bin"

i386-elf-ld -o "full_kernel.bin" -Ttext 0x1000 "kernel_entry.o" "IDT2.o" "kernel.o" --oformat binary

cat "main.bin" "full_kernel.bin" "doublebyte.bin"  > "EchOS.bin"

echo Building successfull!

