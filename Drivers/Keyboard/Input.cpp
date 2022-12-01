#include "IDT.cpp"




void print_letter(uint8_t scancode) {
	switch (scancode) {
		case 0x0:
			print_string("ERROR");
			break;
		
		case 0x1:
			print_string("ESC");
			break;

		case 0x2:
			print_string("1");
			break;

		case 0x3:
			print_string("2");
			break;

		case 0x39:
			print_string("Space");
			break;

		default:
			if (scancode <= 0x7f) {
				print_string("Unknown Key down");
			} else if (scancode <= 0x39 + 0x80) {
				print_string("key up");
				print_letter(scancode - 0x80);
			} else {
				print_string("Unknown key up");
			}
			break;
	}
}

static void keyboard_callback(registers_t *regs) {
	uint8_t scancode = port_byte_in(0x60);
	print_letter(scancode);
	print_nl();
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}