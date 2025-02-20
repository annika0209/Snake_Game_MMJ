//--------------------------------------------------------
// Peripheral driver header file
//--------------------------------------------------------

#include "core_cm0.h"           // Cortex-M3 processor and core peripherals


//--------------------------------------------------------
//           Peripheral memory map    
//--------------------------------------------------------

#define AHB_VGA_BASE        0x50000000
#define AHB_UART_BASE       0x51000000
#define AHB_TIMER_BASE      0x52000000

//--------------------------------------------------------
//           Peripheral type define    
//--------------------------------------------------------

// Timer define
typedef struct
{
    volatile unsigned int INITVALUE;        
    volatile unsigned int CURVALUE;         
    volatile unsigned int CONTROL;       
    volatile unsigned int CLEAR;        
} TIMER_TypeDef;

// UART define 
typedef struct
{
    volatile unsigned int DATA;  
    volatile unsigned int STATUS; 
} UART_TypeDef;

// VGA define 
typedef struct
{
    volatile unsigned int CONSOLE;        
    volatile unsigned int IMG; 
} VGA_TypeDef;


//--------------------------------------------------------
// Peripheral instances define
//--------------------------------------------------------

#define TIMER       ((TIMER_TypeDef *)      AHB_TIMER_BASE )
#define UART        ((UART_TypeDef *)       AHB_UART_BASE  )
#define VGA         ((VGA_TypeDef *)        AHB_VGA_BASE   )

//--------------------------------------------------------
// Peripheral driver functions
//--------------------------------------------------------

void timer_configure(int load_value, int prescale, int mode);		// Configure TIMER
void timer_enable(void);       																	// Enable TIMER
void timer_irq_clear(void);     																// Clear TIMER IRQ

void vga_draw_pixel(int rgb, int img_y, int img_x);									// Draw a pixel

