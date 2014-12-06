#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "flat.h"

flat::flat()
{
  data = NULL;
}

flat::~flat()
{
  if(data) { delete[] data; }
}

bool flat::set_data(uint8_t const *_data)
{
  int idx;

  data = new uint8_t[FLAT_NUM_BYTES];
  
  memcpy(&data[0], _data, FLAT_NUM_BYTES);

  return true;
}

uint8_t const *flat::get_pixel(int x, int y)
{
  // FIXME: assert x,y are sane
  return &data[(y*FLAT_WIDTH)+x];
}

void flat::print_html_file(char const *filename, palette const *pal)
{
  FILE *f;
  color_rgb const *color;

  f = fopen(filename, "wt");
  fprintf(f, "<html>\n");
  fprintf(f, "<body>\n");
  fprintf(f, "<table>\n");
  fprintf(f, "<tr>\n");
  for(int i=0; i<FLAT_NUM_BYTES; i++)
  {
    color = pal->get_color(data[i]);
    fprintf(f, "<td style=\"width: 8px; height: 8px; background-color:#%02x%02x%02x;\"></td>\n", color->r, color->g, color->b);
    if(i%FLAT_WIDTH == (FLAT_WIDTH-1)) { fprintf(f, "</tr><tr>\n"); }
  }
  fprintf(f, "</tr>\n");
  fprintf(f, "</table>\n");
  fprintf(f, "</body>\n");
  fprintf(f, "</html>\n");
  fclose(f);
}