#pragma once

extern "C"
{
#include "GL_image_display.h"
}

#include <FL/Fl_Gl_Window.H>

class Fl_Gl_Image_Widget : public Fl_Gl_Window
{
protected:
    GL_image_display_context_t m_ctx;
    int                        m_last_drag_update_xy[2];

    struct UpdateImageCache
    {
        UpdateImageCache();
        ~UpdateImageCache();
        void dealloc(void);

        bool save( int         _decimation_level,
                   const char* _image_filename,
                   const char* _image_data,
                   int         _image_width,
                   int         _image_height,
                   int         _image_bpp,
                   int         _image_pitch);
        bool apply(Fl_Gl_Image_Widget* w);

        int   decimation_level;
        char* image_filename;
        char* image_data;
        int   image_width;
        int   image_height;
        int   image_bpp;
        int   image_pitch;
    } m_update_image_cache;


public:
    Fl_Gl_Image_Widget(int x, int y, int w, int h);

    virtual ~Fl_Gl_Image_Widget();

    void draw(void);

    virtual int handle(int event);

    /////// C API wrappers
    ///////
    /////// these directly wrap the GL_image_display.h C API. The arguments and
    /////// function names are the same, except for the leading context: we pass
    /////// &m_ctx
    ///////
    /////// Each of these is virtual, so a subclass could override the
    /////// implementation
    virtual
    bool update_image( int decimation_level         = 0,
                          // Either this should be given
                          const char* image_filename   = NULL,
                          // Or these should be given
                          const char* image_data       = NULL,
                          int         image_width      = 0,
                          int         image_height     = 0,
                          int         image_bpp        = 0,
                          int         image_pitch      = 0);

    virtual
    bool set_panzoom(double x_centerpixel, double y_centerpixel,
                     double visible_width_pixels);

    virtual
    bool map_pixel_viewport_from_image(double* xout, double* yout,
                                       double x, double y);

    virtual
    bool map_pixel_image_from_viewport(double* xout, double* yout,
                                       double x, double y);

    virtual
    bool set_lines(const GL_image_display_line_segments_t* line_segment_sets,
                   int Nline_segment_sets);
};
