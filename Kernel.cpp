// gcc 7.4.0

#include "Drivers/Typetext.cpp"
#include "Drivers/Keyboard/IDT.cpp"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" void main()
{
	clear_screen();
	print_string("Installing all service routines \n");
	isr_install();

	print_string("Enabling  extern interrupts \n");
	asm volatile("sti");

	print_string("Setting the keyboard. \n");
	init_keyboard();
}

