#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

typedef struct {
	uint16_t low_offset;
	uint16_t selector;
	uint8_t always0;
	uint8_t flags;
	uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;



idt_gate_t idt[256];

void set_idt_gate(int n, uint32_t handler) {
	idt[n].low_offset = low_16(handler));
	idt[n].selector = 0x08;
	idt[n].always0 = 0;

	idt[n].flags = 0x8E;
	idt[n].high_offset = high_16(handler);
}

// Error messages.
char *exception_messages[] = {
	"Division by zero",
	"Debug",
	"Reserved"
	
};

void isr_handler(register *r) {
	print_string(exception_messages[r->int_no]);
	print_nl();
}

typedef struct {
	uint32_t ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

[extern isr_handler]


typedef void (*isr_t)(registers_t *);

ist_t interrupt_handlers[256];

void irq_handler(registers_t *r) {
	if (interrupt_handlers[r->int_no] != 0) {
		isr_t handler = interrupt_handlers[r->int_no];
		handler(r);
	}

	port_byte_out(0x20, 0x20);
	if (r->int_no < 40) {
		port_byte_out(0xA0, 0x20);
	}
}

typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idt_register_t;

void load_idt() {
	idt_reg.base = (uint32_t) &idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
	asm volatile("lidt (%0)" : : "r"(&idt_reg));
}

void isr_install() {
	set_idt_gate(0, (uint32_t) isr0);
	set_idt_gate(1, (uint32_t) isr1);

	set_idt_gate(31, (uint32_t) isr31);

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

	set_idt_gate(32, (uint32_t)irq0);

	set_idt_gate(39, (uint32_t)irq7);

	set_idt_gate(40, (uint32_t)irq8);

	set_idt_gate(47, (uint32_t)irq15);

	load_idt();
}




	

