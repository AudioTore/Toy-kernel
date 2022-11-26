#include <stdint.h>

void print_string(int colour, const char *string)
{
	volatile char *video = (volatile char*)0xb8000;
	while (*string != 0)
	{
		*video++ = *string++;
		*video = colour;
	}
}


extern "C" void input_keyboard(uint8_t scancode) {
	switch (scancode) {
		case 0x0:
			print_string(15, "Invaild..");
			break;

		case 0x1:
			print_string(15, "ESC");
			break;
			
	}
}
