// gcc 7.4.0

#include "Drivers/Typetext.cpp"
//#include "Drivers/Keyboard/IDT.cpp"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "Drivers/Keyboard/IDT.cpp"
#include "Drivers/Keyboard/Input.cpp"


extern "C" void main()
{
    isr_install(); //installs all ISRs and irqs
    asm volatile("sti"); //enables interrupts
    init_keyboard(); // starts keyboard 
    *((char*)(0xb8000)) = getch(); //demonstration

}

