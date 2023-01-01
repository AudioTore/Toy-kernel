int compare_string(char s1[], char s2[]) {
	int i;
	for (i = 0; s1[i] == s2[i]; i++) {
		if(s1[i] == '\0') return 0;
	}
	return s1[i] - s2[i];
}



void execute_command(char *input) {
    if (compare_string(input, "system.shutdown;") == 0) {
        print_string("Stopping the CPU. Bye!\n");
	asm volatile("hlt");
    }
    else if (compare_string(input, "system.reboot;") == 0) {
	print_string("Test \n");
    }
    else if (compare_string(input, "help;") == 0) {
	print_string("Test \n");
    }
    else if (compare_string(input, "console.clear;") == 0)
    {
	clear_screen();
    }
    else if (compare_string(input, "open.calculator;") == 0)
    {
        print_string("Test \n");
    }
    else if (compare_string(input, "system.about;") == 0)
    {
    	print_string("System OS: EchOS \n");
	print_string("Version: 1.4 \n");
	print_string("Release date: [EARLY ACCESS] \n");
	print_string("Language written in: C++ , assembly \n");
	print_string("Developer: audioTore341 (Github) \n");
    }
    else {
	print_string("'"); // '
	print_string(input); // 'input
	print_string("' Is not a vaild command."); // 'input'
	print_string("\n");
	print_string("NOTE: Every command has a capital at the beginning and a '();' at the end. \n");
    }
    print_string("[0:/]: ");
}
