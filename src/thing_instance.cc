#include <stdio.h>
#include <math.h>

#include "common.h"
#include "thing_instance.h"

//#define DEBUG_PRINTING
#include "debug.h"

thing_instance::thing_instance()
{
}

thing_instance::~thing_instance()
{
}

bool thing_instance::read_from_lump_data(uint8_t const *lump_data)
{
  map_position.set_x(*(( int16_t*)lump_data)); lump_data += 2;
  map_position.set_y(*(( int16_t*)lump_data)); lump_data += 2;
  facing_angle     = (*(( int16_t*)lump_data))/256.0 ; lump_data += 2;
  thing_type       = *((uint16_t*)lump_data) ; lump_data += 2;
  flags            = *((uint16_t*)lump_data) ; lump_data += 2;

  // convert angle from degrees to radians
  facing_angle = DEG_TO_RAD(facing_angle+90);

  // get the definition (description, etc.)
  defn = thing_definition_lookup(thing_type);

  return true;
}

