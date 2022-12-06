#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define IDT_ENTRIES 256
#define low_16(address) (uint16_t)((address) & 0xFFFF
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)


typedef struct {
	uint16_t low_offset;
	uint16_t selector;
	uint8_t always0;
	uint8_t flags;
	uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) registers_t;

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_registers_t;

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();
/* IRQ definitions */
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();



idt_registers_t idt_reg;
idt_gate_t idt[256];




// Error messages.
char *exception_messages[] = {
	"Division by zero",
	"Debug",
	"Reserved"
};


void set_idt_gate(int n, uint32_t handler) {
	idt[n].low_offset = low_16(handler));
	idt[n].selector = 0x08;
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler);
}




extern "C" void isr_handler(registers_t *r) {
	print_string(exception_messages[r->int_no]);
}






typedef void (*isr_t)(registers_t *);

isr_t interrupt_handlers[255];


void  register_interrupt_handler(unsigned char n, isr_t handler) {
    interrupt_handlers[n] = handler;
}


extern "C" void irq_handler(registers_t r) {

    if (r.int_no >= 40) port_byte_out(0xA0, 0x20); /* slave */
    port_byte_out(0x20, 0x20); /* master */


    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
		handler(&r);
    }
}


void load_idt() {
	idt_reg.base = (uint32_t) &idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
	asm volatile("lidt (%0)" : : "r"(&idt_reg));
}

typedef unsigned int u32;

extern "C" void isr_install() {
    set_idt_gate(0, (u32)isr0);
    set_idt_gate(1, (u32)isr1);
    set_idt_gate(2, (u32)isr2);
    set_idt_gate(3, (u32)isr3);
    set_idt_gate(4, (u32)isr4);
    set_idt_gate(5, (u32)isr5);
    set_idt_gate(6, (u32)isr6);
    set_idt_gate(7, (u32)isr7);
    set_idt_gate(8, (u32)isr8);
    set_idt_gate(9, (u32)isr9);
    set_idt_gate(10, (u32)isr10);
    set_idt_gate(11, (u32)isr11);
    set_idt_gate(12, (u32)isr12);
    set_idt_gate(13, (u32)isr13);
    set_idt_gate(14, (u32)isr14);
    set_idt_gate(15, (u32)isr15);
    set_idt_gate(16, (u32)isr16);
    set_idt_gate(17, (u32)isr17);
    set_idt_gate(18, (u32)isr18);
    set_idt_gate(19, (u32)isr19);
    set_idt_gate(20, (u32)isr20);
    set_idt_gate(21, (u32)isr21);
    set_idt_gate(22, (u32)isr22);
    set_idt_gate(23, (u32)isr23);
    set_idt_gate(24, (u32)isr24);
    set_idt_gate(25, (u32)isr25);
    set_idt_gate(26, (u32)isr26);
    set_idt_gate(27, (u32)isr27);
    set_idt_gate(28, (u32)isr28);
    set_idt_gate(29, (u32)isr29);
    set_idt_gate(30, (u32)isr30);
    set_idt_gate(31, (u32)isr31);

	port_byte_out(0x20, 0x11);
	port_byte_out(0xA0, 0x11);

	port_byte_out(0x21, 0x20);
	port_byte_out(0xA1, 0x28);

	port_byte_out(0x21, 0x04);
	port_byte_out(0xA1, 0x02);

	port_byte_out(0x21, 0x01);
	port_byte_out(0xA1, 0x01);

	port_byte_out(0x21, 0x0);
	port_byte_out(0xA1, 0x0);

    set_idt_gate(32, (u32)irq0);
    set_idt_gate(33, (u32)irq1);
    set_idt_gate(34, (u32)irq2);
    set_idt_gate(35, (u32)irq3);
    set_idt_gate(36, (u32)irq4);
    set_idt_gate(37, (u32)irq5);
    set_idt_gate(38, (u32)irq6);
    set_idt_gate(39, (u32)irq7);
    set_idt_gate(40, (u32)irq8);
    set_idt_gate(41, (u32)irq9);
    set_idt_gate(42, (u32)irq10);
    set_idt_gate(43, (u32)irq11);
    set_idt_gate(44, (u32)irq12);
    set_idt_gate(45, (u32)irq13);
    set_idt_gate(46, (u32)irq14);
    set_idt_gate(47, (u32)irq15);


	load_idt();
}
