// gcc 7.4.0

// Core part of the OS..


#include "memory.hpp"
#include "Drivers/Typetext.cpp"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Drivers/Keyboard/IDT.cpp"
#include "Drivers/Keyboard/Scancode.cpp"


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" void main()
{
	 clear_screen();
    	 print_string("Installing ISRS.. \n");
   	 isr_install();

    	 print_string("Enabling ints.. \n");
    	 asm volatile("sti");

   	 print_string("Initializing keyboard (IRQ 1)");
    	 init_keyboard();

	 clear_screen();
	 print_string(isolate_args("eeeeeee.s args ();",strlen("eeeeeee.s args ();")));
	 print_string("\n");
	 print_string("> ");

    	 
}

