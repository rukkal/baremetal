#include "terminal.h"

extern void kernel_main();

extern "C" void __attribute__((noreturn)) setup_cpu(void)
{
	auto term = terminal{};
    term.initialize_screen();
	term.write_line("Setting up CPU long mode...");
    
    //TODO: set up long mode
    
    volatile bool b=true;
    while(b);
    //TODO: run kernel
    //kernel_main();
    
    __builtin_unreachable();
}
