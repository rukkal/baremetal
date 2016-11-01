#include "terminal.h"

extern void kernel_main();

class cpu_configuration
{
public:
    void run()
    {
        term.initialize_screen();
        
        if(!cpu_supports_cpuid())
        {
            panic("cpu doesn't support CPUID");
        }
        term.write_line("CPUID support detected");
        
        if(!cpu_supports_long_mode())
        {
            panic("cpu doesn't support long mode");
        }
        term.write_line("long mode support detected");
        
        setup_long_mode();
        term.write_line("switched to long mode");
    }

private:
    bool cpu_supports_cpuid()
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
     
    bool cpu_supports_long_mode()
    {
        uint32_t cpu_id_response=0;

        //check that intel extended functions are supported (necessary to detect long mode support)
        asm volatile("mov $0x80000000, %%eax; cpuid": "=a" (cpu_id_response) : : "ebx", "ecx", "edx");
        if(cpu_id_response < 0x80000001)
        {
            return false;
        }
        
        //check that long mode is supported
        asm volatile("mov $0x80000001, %%eax; cpuid": "=d" (cpu_id_response) : : "eax", "ebx", "ecx");
        if((cpu_id_response & (1<<29)) == 0)
        {
            return false;
        }

        return true;
    }

    void setup_long_mode()
    {
	    term.write_line("setting up CPU long mode...");
        //TODO
    }

    void panic(const char* message)
    {
       term.write_line("kernel panic!");
       term.write_line("reason:");
       term.write_line(message);
       asm volatile("cli"); //disable interrupts
       volatile bool forever=true;
       while(forever)
           ;
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
