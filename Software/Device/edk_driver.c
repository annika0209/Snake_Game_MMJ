//--------------------------------------------------------
// Peripheral driver functions
//--------------------------------------------------------

#include "EDK_CM.h"
#include "edk_driver.h"

//---------------------------------------------
// VGA driver function
//---------------------------------------------

//Draw a pixel to the image buffer
void vga_draw_pixel (int rgb, int img_y, int img_x)
{
    //100x120 resolution
    int addr;
    addr = img_y * 128 + img_x;
    *(&(VGA->IMG) + addr) = rgb;
}

//---------------------------------------------
// Timer driver function
//---------------------------------------------

//Timer configuration
//Control register: [0]: timer enable, [1] mode (free-run or reload) [2]: prescaler
void timer_configure(int load_value, int prescale, int mode)
{
    int control;
    int prescale_bits;
    
    if (prescale == 16)
        prescale_bits = 0x01;    
    else
        prescale_bits = 0x00;    
        
    control = ((prescale_bits << 2)|(mode << 1));
		
    TIMER->INITVALUE = load_value;
    TIMER->CONTROL = control;
    TIMER->CLEAR = 1;
}

// timer enable
void timer_enable(void)
{
    int control;
    
    control = TIMER->CONTROL;
    control = control | 0x1;
    TIMER->CONTROL = control;                    
}

// clear interrupt request from timer
void timer_irq_clear(void)
{
    TIMER->CLEAR = 0x01;                    
}
