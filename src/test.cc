#include <stdio.h>

#include "wad_file.h"
#include "palettes.h"
#include "colormaps.h"
#include "flats.h"
#include "sprites.h"
#include "patches.h"
#include "wall_textures.h"

int main(int argc, char **argv)
{
  wad_file w;

  printf("Reading WAD file.\n");
  w.read("data/Doom1.WAD");

  printf("Initializing...\n");
  palettes_init(&w);
  colormaps_init(&w);
  flats_init(&w);
  sprites_init(&w);
  patches_init(&w);
  wall_textures_init(&w);

  printf("\nSuccess!\n\n");

  printf("Shutting down...\n");
  wall_textures_destroy();
  patches_destroy();
  sprites_destroy();
  flats_destroy();
  colormaps_destroy();
  palettes_destroy();

  return 0;
}
