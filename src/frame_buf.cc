/******************************************************************************
 * 2D Coordinate system:
 *
 * y=0                -> top    of screen
 * y=(frame_height-1) -> bottom of screen
 *
 * x=0                -> left   of screen
 * x=(frame_width-1)  -> right  of screen
 *
 ******************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "frame_buf.h"
#include "ui.h"

//#define DO_RANGE_CHECKING
#define BYTES_PER_PIXEL 4
#define BYTES_PER_PIXEL_SHIFT 2

static int frame_width, frame_height;
static int frame_num_bytes;
static uint8_t *frame;

bool frame_buf_init(int width, int height)
{
  frame_width     = width;
  frame_height    = height;
  frame_num_bytes = frame_width*frame_height*BYTES_PER_PIXEL;
  frame = new uint8_t[frame_num_bytes];
  ui_resize_window(frame_width, frame_height);
  return true;
}

void frame_buf_destroy()
{
  delete[] frame;
}

void frame_buf_clear(void)
{
  uint32_t *ptr = (uint32_t*)frame;
  for(uint32_t i=0; i<frame_width*frame_height; i++)
  {
    *(ptr++) = 0xff000000;
  }
}

void frame_buf_flush_to_ui(void)
{
  ui_draw_image(frame, frame_width, frame_height);
}

void frame_buf_overlay_pixel(int x, int y, color_rgba const *color)
{
  #ifdef DO_RANGE_CHECKING
  if(!(x>=0 && x<frame_width && y>=0 && y<frame_height))
  {
    printf("WARNING: attempted to draw pixel at (%d,%d)\n", x, y);
    return;
  }
  #endif

  uint8_t *ptr;
  ptr = frame + (((y*frame_width) + x)*BYTES_PER_PIXEL);
  *(ptr+0) = (color->r * color->a/255.0) + (*(ptr+0) * (255.0-color->a)/255.0);
  *(ptr+1) = (color->g * color->a/255.0) + (*(ptr+1) * (255.0-color->a)/255.0);
  *(ptr+2) = (color->b * color->a/255.0) + (*(ptr+2) * (255.0-color->a)/255.0);
  *(ptr+3) = 255.0; // ?
}

void frame_buf_draw_pixel(int x, int y, color_rgba const *color)
{
  #ifdef DO_RANGE_CHECKING
  if(!(x>=0 && x<frame_width && y>=0 && y<frame_height))
  {
    printf("WARNING: attempted to draw pixel at (%d,%d)\n", x, y);
    return;
  }
  #endif

  uint8_t *ptr;
  ptr = frame + (((y*frame_width) + x)*BYTES_PER_PIXEL);
  *(ptr++) = color->r;
  *(ptr++) = color->g;
  *(ptr++) = color->b;
  *(ptr++) = color->a;
}

void frame_buf_draw_line(int x1, int y1, int x2, int y2, color_rgba const *color)
{
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = abs(delta_x) << 1;
 
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = abs(delta_y) << 1;
 
    frame_buf_draw_pixel(x1, y1, color);
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
 
            error += delta_y;
            x1 += ix;
 
            frame_buf_draw_pixel(x1, y1, color);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
 
            error += delta_x;
            y1 += iy;
 
            frame_buf_draw_pixel(x1, y1, color);
        }
    }
}
