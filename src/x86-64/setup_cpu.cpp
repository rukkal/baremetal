#include "terminal.h"

extern void kernel_main();

void panic()
{
   terminal{}.write_line("kernel panic");
   asm volatile("cli"); //disable interrupts
   volatile bool forever=true;
   while(forever)
       ;
}

class cpu_configuration
{
public:
    void run()
    {
        term.initialize_screen();
        check_cpuid();
        setup_long_mode();
    }

    void check_cpuid()
    {
        if(!is_cpuid_supported())
        {
            term.write_line("CPU doesn't support CPUID");
            panic();
        }
        //TODO: check is x86_64
    }

    bool is_cpuid_supported() const
    {
        uint32_t zero_if_cpuid_not_supported;
        
        asm volatile(
            "pushfl                     #push EFLAGS\t\n\
             pop %%eax                  #eax = EFLAGS\t\n\
             mov %%eax, %%ecx           #ecx = EFLAGS\t\n\
             xor $0x00200000, %%eax     #eax = EFLAGS with flipped ID bit\t\n\
             push %%eax                 #push EFLAGS with flipped ID bit\t\n\
             popfl                      #load EFLAGS with flipped ID bit\t\n\
             pushfl                     #push EFLAGS\t\n\
             pop %%eax                  #eax = modified EFLAGS (ID bit is flipped if CPUID is supported)\t\n\
             push %%ecx                 #push unmodified EFLAGS\t\n\
             popfl                      #restore original EFLAGS\t\n\
             xor %%ecx, %%eax           #eax is zero if CPUID is not supported"
            : "=a" (zero_if_cpuid_not_supported)
            :
            : "ecx");

        return zero_if_cpuid_not_supported != 0;
    }

    void setup_long_mode()
    {
	    term.write_line("Setting up CPU long mode...");
        //TODO
    }

private:
    terminal term;
};

extern "C" void __attribute__((noreturn)) setup_cpu(void)
{
    cpu_configuration{}.run(); 
    //TODO: set up long mode
    
    volatile bool b=true;
    while(b);
    //TODO: run kernel
    //kernel_main();
    
    __builtin_unreachable();
}
