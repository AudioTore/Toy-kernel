
#define IRQ1 33



unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
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
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

char char_getch;
int getch_f =0;


char getch(){
	getch_f =1;
	while(getch_f==1){
	
	}
	return char_getch;
}





static void keyboard_callback(registers_t *regs) {
	uint8_t scancode = port_byte_in(0x60);				
				if (scancode <= 56) {
					getch_f = 0;
					char_getch = kbdus[scancode];
				}
}



/*
char buffer[200];

int indexer =0;
static void keyboard_callback(registers_t *regs) {
	uint8_t scancode = port_byte_in(0x60);
	//print_letter(scancode);
				indexer%=199;
				
				if (scancode <= 56 && scancode != 0x1 ) {
					clear_screen();
					buffer[indexer++]=kbdus[scancode];
					print_string(buffer);
					
				}else if(scancode == 0x1){
					
					indexer =0;
					for(int i =0; i<199;i++){
						buffer[i]=' ';
					}
					clear_screen();
				}
				
}

*/
void init_keyboard() {
	register_interrupt_handler(IRQ1, keyboard_callback);
}


