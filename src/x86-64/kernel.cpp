#include "terminal.h"
 
void __attribute__((noreturn)) kernel_main()
{
    auto term = terminal{};
	term.write_line("Running kernel...");

    __builtin_unreachable();
}
