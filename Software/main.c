
#include "EDK_CM.h"
#include "edk_driver.h"
#include "edk_api.h"
#include "core_cm0.h"			// CMSIS header


volatile static int y = 60;		//volatile: 컴파일러 최적화를 방지하고 변수가 예기치 않게 변경될 수 있음을 나타냄
volatile static int x = 50;
volatile static int d = 0; // 0 = up, 1 = down, 2 = left, 3 = right

int main(void)
{
	y = 50;
	x = 50;
	
	VGA->CONSOLE = 'M';
	
	boundary(BLUE);
	vga_draw_pixel(RED,x,y);
										//인터럽트 우선순위를 설정하고 관리하는 ARM Cortex-M 프로세서의 NVIC기능 (Nested Vectored Interrupt Controller)
	NVIC_SetPriority(Timer_IRQn,0x00);	//NVIC 설정에서 비트 단위 연산이 사용
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

void UART_ISR()		//인터럽트 서비스 루틴(ISR): Timer_ISR과 UART_ISR 함수로, 특정 이벤트 발생 시 자동으로 실행

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
