// Adapted from Tony Weston's post on facebook ESP8266 page


extern "C" {

#include <string.h>
#include <math.h>

}

#include "gfx.hpp"

#define FRAME_DELAY		10			/* The interframe delay in milliseconds */

float px[8],py[8],pz[8];
float tmp;
float xa,ya,za;

int mapx[8],mapy[8];

extern "C" void demo(void* pvParameters)
{
    // Initialize and clear the display
    gfxInit();

    ugfx::display display;
    //const ugfx::display::color_context_experimental ctx(display, White);

    display.clear();

    for(;;)
    {
        // start points..
        px[0]=-50; py[0]=-50; pz[0]=-50;
        px[1]= 50; py[1]=-50; pz[1]=-50;
        px[2]= 50; py[2]= 50; pz[2]=-50;
        px[3]=-50; py[3]= 50; pz[3]=-50;
        px[4]=-50; py[4]=-50; pz[4]=50;
        px[5]= 50; py[5]=-50; pz[5]=50;
        px[6]= 50; py[6]= 50; pz[6]=50;
        px[7]=-50; py[7]= 50; pz[7]=50;



        za=za+.01;
        xa=xa+.02;
        ya=ya+.03;

        // map it.
        for (int i=0; i<8; i++){

        // rotate around z.
        tmp= px[i]*cos(za)-py[i]*sin(za);
        py[i]=px[i]*sin(za)+py[i]*cos(za);
        px[i]=tmp;

        // // rotate around x.
        tmp= py[i]*cos(xa)-pz[i]*sin(xa);
        pz[i]=py[i]*sin(xa)+pz[i]*cos(xa);
        py[i]=tmp;
        //
        // // rotate around y.
        tmp= px[i]*cos(ya)-pz[i]*sin(ya);
        pz[i]=px[i]*sin(ya)+pz[i]*cos(ya);
        px[i]=tmp;

        // project
        float dist=2.2+(pz[i]+80)/80;

        mapx[i] = px[i]/dist +50;
        mapy[i] = py[i]/dist +30;


        }

        constexpr color_t line_color = White;


        // Draw it..
        display.clear();
        display.draw_line(mapx[0],mapy[0],mapx[1],mapy[1], line_color);
        display.draw_line(mapx[1],mapy[1],mapx[2],mapy[2], line_color);
        display.draw_line(mapx[2],mapy[2],mapx[3],mapy[3], line_color);
        display.draw_line(mapx[3],mapy[3],mapx[0],mapy[0], line_color);

        display.draw_line(mapx[4],mapy[4],mapx[5],mapy[5], line_color);
        display.draw_line(mapx[5],mapy[5],mapx[6],mapy[6], line_color);
        display.draw_line(mapx[6],mapy[6],mapx[7],mapy[7], line_color);
        display.draw_line(mapx[7],mapy[7],mapx[4],mapy[4], line_color);

        display.draw_line(mapx[4],mapy[4],mapx[0],mapy[0], line_color);
        display.draw_line(mapx[5],mapy[5],mapx[1],mapy[1], line_color);
        display.draw_line(mapx[6],mapy[6],mapx[2],mapy[2], line_color);
        display.draw_line(mapx[7],mapy[7],mapx[3],mapy[3], line_color);

        display.flush();

        // Delay for a while
    	gfxSleepMilliseconds(FRAME_DELAY);
    }
}
