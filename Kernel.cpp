// gcc 7.4.0

// Our kernel.
// Does exactly what a kernel is supposed to do.
// Setup all our drivers ;)

#include "Drivers/Typetext.cpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Drivers/Keyboard/IDT.cpp"
#include "Drivers/Keyboard/Scancode.cpp"
#include "Drivers/ATA/ata.cpp"
#include "Drivers/fs/readb.cpp"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" void main()
{
	 	
         clear_screen_notext();
         print_string("Booting EchOS...\n");
         isr_install();

         asm volatile("sti");

         print_string("Initializing keyboard Driver [PS2] \n");
         // init_keyboard();
	 
	 
	 uint32_t target;
	 read_sectors_ATA_PIO(target, 0x0, 1);
	
	 int i;
	 i = 0;
	 uint32_t bwrite[512];
	 for (i = 0; i < 512; i++)
	 {
	 	bwrite[i] = 0x0;
	 }
	 write_sectors_ATA_PIO(0x0, 2, bwrite);

	 print_string("Reading.. \n");
	 read_sectors_ATA_PIO(target, 0x0, 1);
	 
	 clear_screen_notext();
	 clear_screen();
         print_string("EchOS has successfully booted! \n");
	 print_string("Welcome! \n");

	 print_string("[C:/]: ");
         init_keyboard();

}

