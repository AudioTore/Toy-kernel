// gcc 7.4.0

#include "Drivers/Typetext.cpp"
#include "Shell/Shell.cpp"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern "C" void main()
{
	terminal_initialize();
	
	/*
	for (int i = 0; i < 100000; i++)
	{
		terminal_writestring("EchOS has successfully booted!");
	}
	*/
	terminal_writestring("Testing testing.");
	terminal_writestring("\n Testing testing.");
	
	
}






