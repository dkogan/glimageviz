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

    int m_decimation_level;

    struct UpdateImageCache
    {
        UpdateImageCache();
        ~UpdateImageCache();
        void dealloc(void);

        bool save( const char* _filename,
                   const char* _image_data,
                   int         _image_width,
                   int         _image_height,
                   bool        _upside_down);
        bool apply(Fl_Gl_Image_Widget* w);

        char* image_filename;
        char* image_data;
        int   image_width;
        int   image_height;
        bool  upside_down;
    } m_update_image_cache;


public:
    Fl_Gl_Image_Widget(int x, int y, int w, int h,
                       int decimation_level = 0);

    virtual ~Fl_Gl_Image_Widget();

    bool update_image( // Either this should be given
                       const char* image_filename,
                       // Or these should be given
                       const char* image_data       = NULL,
                       int         image_width      = 0,
                       int         image_height     = 0,
                       bool        upside_down = false);

    void draw(void);

    virtual int handle(int event);
};
