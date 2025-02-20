//--------------------------------------------------------
// Application Programming Interface (API) functions
//--------------------------------------------------------
#include "EDK_CM.h"
#include "edk_driver.h"
#include "edk_api.h"
#include "core_cm0.h"

//---------------------------------------------
// Draw a rectangle on the screen
//---------------------------------------------
void rectangle(int x1, int y1, int x2, int y2, int color)
{
    int i, j;
    for (i = x1; i < x2; i++) {
        for (j = y1; j < y2; j++) {
            vga_draw_pixel(color, j, i);
        }
    }
}


//---------------------------------------------
// Draw the boundary of the image region
//---------------------------------------------
void boundary(int color)
{
    rectangle(0,0,WIDTH,HEIGHT,color);
		rectangle(1,1,WIDTH-1,HEIGHT-1,BLACK);
}
