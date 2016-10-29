#include <stddef.h>
#include <stdint.h>
 
namespace vga
{

static constexpr size_t WIDTH = 80;
static constexpr size_t HEIGHT = 25;

enum class color {
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15,
};

static inline uint16_t entry(unsigned char c, color foreground, color background)
{
    auto entry_color = static_cast<uint8_t>(foreground) | (static_cast<uint8_t>(background) << 4);
	return static_cast<uint16_t>(c) | (static_cast<uint16_t>(entry_color) << 8);
}
 
}

class terminal
{
public:
    void set_foreground_color(vga::color c)
    {
        color_foreground = c;
    }

    void set_background_color(vga::color c)
    {
        color_background = c;
    }

    void initialize_screen(void)
    {
    	row = 0;
    	column = 0;
        for (size_t y = 0; y < vga::HEIGHT; y++)
        {
    		for (size_t x = 0; x < vga::WIDTH; x++)
            {
                putchar_at(' ', x, y);
    		}
    	}
    }
     
    void write_line(const char* data)
    {
        for(const char* pos=data; *pos!=0; ++pos)
        {
            if(column>=vga::WIDTH)
                break;
            putchar_at(*pos, column++, row);
        }
        column = 0;
        ++row;
    }

private:
    void putchar_at(char c, size_t x, size_t y)
    {
    	auto entry = vga::entry(c, color_foreground, color_background);
        const size_t index = y * vga::WIDTH + x;
    	vga_buffer[index] = entry;
    }

private: 
    size_t row;
    size_t column;
    vga::color color_foreground;
    vga::color color_background;
    uint16_t* vga_buffer = reinterpret_cast<uint16_t*>(0xB8000);
};
 
 
#if defined(__cplusplus)
extern "C" //C linkage to be called from _start
#endif
void kernel_main(void) {
	auto term = terminal{};
    term.set_background_color(vga::color::BLACK);
    term.initialize_screen();
    term.set_background_color(vga::color::MAGENTA);
    term.set_foreground_color(vga::color::BLACK);
	term.write_line("#################################");
	term.write_line("    Welcome to Esmeralda OS      ");
	term.write_line("#################################");
}
