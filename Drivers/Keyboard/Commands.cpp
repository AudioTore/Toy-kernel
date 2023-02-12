#include "combat_op.cpp"
#include "../ACPI/rsdp.cpp"

#define KBRD_INTRFC 0x64
#define KBRD_BIT_KDATA 0
#define KBRD_BIT_UDATA 1
#define KBRD_IO 0x60
#define KBRD_RESET 0xFE

#define bit(n) (1<<(n))

#define check_flag(flags, n) ((flags) & bit(n))

unsigned char inb(unsigned short port)
{
	unsigned char result;

	__asm__("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}
void port_word_out(unsigned short port, unsigned short data) // The outw version for power management.
{
	__asm__("outw %%ax, %%dx" : : "a" (data), "d" (port));
}

void reboot()
{
	uint8_t temp;
	asm volatile("cli");

	do
	{
		temp = inb(KBRD_INTRFC);
		if (check_flag(temp, KBRD_BIT_KDATA) != 0)
			inb(KBRD_IO);
	} while (check_flag(temp, KBRD_BIT_UDATA) != 0);

	port_byte_out(KBRD_INTRFC, KBRD_RESET);
	
loop:
	asm volatile("hlt");
	goto loop;
}

int compare_string(char s1[], char s2[]) {
	int i;
	for (i = 0; s1[i] == s2[i]; i++) {
		if(s1[i] == '\0') return 0;
	}
	return s1[i] - s2[i];
}



void execute_command(char *input) {
    if (compare_string(input, "System.Shutdown();") == 0) {
	port_word_out(0x604, 0x2000); // Qemu.
	port_word_out(0x4004, 0x3400); // Virtualbox.
    }
    else if (compare_string(input, "System.Reboot();") == 0) {
	reboot();
    }
    else if (compare_string(input, "Help();") == 0) {
	print_string("Note: Every command ends with a '();' \n");
	print_string("Command List: \n");
	print_string("================================================================================ \n");
	print_string("Disk.GetInformation(); - Tells you information of the current drive \n");
	print_string("Disk.ListDir(); - List all the files in the current directory \n");
	print_string("File.create [file] - Creates a File. Takes two or more arguments. \n");
	print_string("File.delete [file] - Deletes a File. Takes two or more arguments. \n");
	print_string("File.read [file] - Reads and prints the contents of a text file. Takes two or more arguments. \n");
	print_string("Directory.create [directory] - Creates a directory. Takes two or more arguments. \n");
        print_string("Directory.delete [directory] - Deletes a directory. Takes two or more arguments. \n");
        print_string("Open.TextPad(); - Allows you to type text and save it. \n");
        print_string("Open.Tour(); - Take a tour and teaches you about how to use EchOS! \n");
        print_string("System.Shutdown(); - Shuts the OS Down. (Please use this) \n");
        print_string("System.Reboot(); - Reboots the OS. \n");
        print_string("Open.Calculator(); - Opens the systems calculator. \n");
        print_string("BackgroundColor.Change(); - Changes the terminals background color. \n");
        print_string("System.About(); - Tells more information about the OS \n");
        print_string("CMD.Clear(); - Clears the console. \n");
        print_string("Execute.Ticktacktoe(); \n");
        print_string("Orlov [file] - Use the orlov language to build apps. mov ah, 'Hello' \n");
        print_string("================================================================================ \n");
    }
    else if (compare_string(input, "combat;") == 0) {
		clear_screen();
		disp_map();
		print_string("\n\n");
    }
    else if (compare_string(input, "CMD.Clear();") == 0)
    {
		clear_screen();
	
    }
    else if (compare_string(input, "Open.Calculator();") == 0)
    {
        print_string("Test \n");
    }
    else if (compare_string(input, "System.About();") == 0)
    {
    	print_string("System OS: EchOS \n");
	print_string("Version: 1.6 \n");
	print_string("Release date: [EARLY ACCESS] \n");
	print_string("Language written in: C++ , assembly \n");
	print_string("Developer: audioTore341 (Github) \n");
    }
    else if (compare_string(input, "Open.Tour();") == 0)
    {
    
    }
    else if (compare_string(input, "Open.TextPad();") == 0)
    {
    
    }
    else if (compare_string(input, "Disk.GetInformation();") == 0)
    {
    
    }
    else if (compare_string(input, "Disk.ListDir();") == 0)
    {
    	
    }
    else if (compare_string(input, "File.create ") == 0)
    {
    
    }
    else if (compare_string(input, "Execute.Ticktacktoe();") == 0)
    {
    
    }
    else {
	print_string("'"); // '
	print_string(input); // 'input
	print_string("' Is not a vaild command."); // 'input'
	print_string("\n");
	print_string("NOTE: Every command has a capital at the beginning and a '();' at the end. \n");
    }
    print_string("[C:/]: ");
	
}
