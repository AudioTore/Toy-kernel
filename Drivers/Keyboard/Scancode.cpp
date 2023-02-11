#define IRQ1 33
#define SC_MAX 57
#define ENTER 0x1C
#define BACKSPACE 0x0E

// Commands.
#include "Commands.cpp"


int string_length(char s[]) {
	int i = 0;
	while(s[i] != '\0') {
		++i;
	}
	return i;
}

void append(char s[], char n) {
	int len = string_length(s);
	s[len] = n;
	s[len + 1] = '\0';
}

static char key_buffer[256];
static char cap_key_buffer[128];

const char scancode_to_shift[] = {
     0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '+', /*'´' */0, '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\'', '<',   0,		/* Left shift */
 '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,  '<',
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

const char scancode_to_char[] = {
     0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '+', /*'´' */0, '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '<',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '-',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,  '<',
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/*
void print_letter(uint8_t scancode) {
	switch (scancode) {
		case 0x0:
			print_string("ERROR!");
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

		default:
			if (scancode <= 0x7f) {
				print_string("Unknown key down");
			} else if (scancode <= 0x39 + 0x80) {
				print_string("Key up ");
				print_letter(scancode - 0x80);
			} else {
				print_string("Unknown key up");
			}
			break;
	}
}

*/
void print_backspace() {
    int newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor);
    set_cursor(newCursor);
}

bool backspace(char buffer[]) {
	int len = string_length(buffer);
	if (len > 0) {
		buffer[len - 1] = '\0';
		return true;
	} else {
		return false;
	}
}

/*
int compare_string(char s1[], char s2[]) {
	int i;
	for (i = 0; s1[i] == s2[i]; i++) {
		if(s1[i] == '\0') return 0;
	}
	return s1[i] - s2[i];
}
*/

/*
void execute_command(char *input) {
    if (compare_string(input, "exit") == 0) {
        print_string("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    print_string("Unknown command: ");
    print_string(input);
    print_string("\n> ");
}
*/

bool shift_hold = false;

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    // return scancode_to_shift[scancode];

    // scancode_to_captial[scancode];

    unsigned char c = 0;
    if (scancode > SC_MAX) return;
    

    // If shift is pressed.    
    if (scancode == 0x2A)
    {
    	shift_hold = true;
	print_string("Pressed!");
    } if (scancode == 0xAA) {
	shift_hold = false;
    	print_string("Worked!");
    }
    /*
    if (scancode == BACKSPACE) {
        if (backspace(key_buffer) == true) {
            print_backspace();
        }
    } else if (scancode == ENTER) {
        print_string("\n");
        execute_command(key_buffer);
        key_buffer[0] = '\0';
    } else {
	if (shift_hold == true)
	{
		char letter = scancode_to_shift[(int) scancode];
        	append(key_buffer, letter);
        	char str[2] = {letter, '\0'};
        	print_string(str);
	}
	else if (shift_hold == false)
	{
		char letter = scancode_to_char[(int) scancode];
        	append(key_buffer, letter);
        	char str[2] = {letter, '\0'};
        	print_string(str);
	}
    }
    */
}

void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}







