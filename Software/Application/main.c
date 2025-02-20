
#include "EDK_CM.h"
#include "edk_driver.h"
#include "edk_api.h"
#include "core_cm0.h"			// CMSIS header


volatile static int y = 60;
volatile static int x = 50;
volatile static int d = 0; // 0 = up, 1 = down, 2 = left, 3 = right

int main(void)
{
	y = 50;
	x = 50;
	
	VGA->CONSOLE = 'M';
	
	boundary(BLUE);
	vga_draw_pixel(RED,x,y);
	
	NVIC_SetPriority(Timer_IRQn,0x00);
	NVIC_EnableIRQ(Timer_IRQn);
	NVIC_SetPriority(UART_IRQn,0x40);
	NVIC_EnableIRQ(UART_IRQn);
	
	timer_configure(10000000,1,1);
	timer_enable();
		
	while(1);
}

void Timer_ISR()
{
	VGA->CONSOLE = 'T';
	timer_irq_clear();				// Timer interrupt clear
	if(d==UP){
		if(y!=1){
			vga_draw_pixel(BLACK,y,x);
			y--;
			vga_draw_pixel(RED,y,x);
		}
	}else if(d==DOWN){
		if(y!=HEIGHT-2){
			vga_draw_pixel(BLACK,y,x);
			y++;
			vga_draw_pixel(RED,y,x);
		}
	}else if(d==LEFT){
		if(x!=1){
			vga_draw_pixel(BLACK,y,x);
			x--;
			vga_draw_pixel(RED,y,x);
		}
	}else{
		if(x!=WIDTH-2){
			vga_draw_pixel(BLACK,y,x);
			x++;
			vga_draw_pixel(RED,y,x);
		}
	}
}

void UART_ISR()
{
	static char in;
	in = UART->DATA;
	VGA->CONSOLE = in;
	if(in=='w')
		d = UP;
	else if(in=='s')
		d = DOWN;
	else if(in=='a')
		d = LEFT;
	else if(in=='d')
		d = RIGHT;
}
