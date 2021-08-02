#include <string.h>
#include <stdio.h>
#include <getopt.h>

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <GL/gl.h>
#include <math.h>

extern "C"
{
#include "util.h"
#include "glimageviz.h"
}

#include "glimageviz-fltk.hh"



#define WINDOW_W   800
#define WINDOW_H   600
#define DECIMATION 3

class GLWidget;

static Fl_Double_Window* g_window;
static GLWidget*         g_gl_widgets[4];



static
void timer_callback(void* cookie __attribute__((unused)))
{
    static int c = 0;
    char buf[256];
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            sprintf(buf, "/tmp/images/frame0016%d-pair%d-cam%d.jpg", c, i, j);
            g_gl_widgets[2*i+j]->update_image(buf);
        }

    Fl::repeat_timeout(1.0, timer_callback);
    if(++c == 10) c = 0;
}

int main(int argc, char** argv)
{
    Fl::lock();

    g_window = new Fl_Double_Window( WINDOW_W, WINDOW_H, "OpenGL image visualizer" );

    int w = WINDOW_W/2;
    int h = WINDOW_H/2;
    g_gl_widgets[0] = new GLWidget(0, 0, w, h,
                                   DECIMATION);
    g_gl_widgets[1] = new GLWidget(w, 0,
                                   WINDOW_W-w,
                                   h,
                                   DECIMATION);
    g_gl_widgets[2] = new GLWidget(0, h,
                                   w,
                                   WINDOW_H-h,
                                   DECIMATION);
    g_gl_widgets[3] = new GLWidget(w, h,
                                   WINDOW_W-w,
                                   WINDOW_H-h,
                                   DECIMATION);

    g_window->resizable(g_window);
    g_window->end();
    g_window->show();

    Fl::add_timeout(1.0, timer_callback);

    Fl::run();

    return 0;
}
