#ifndef __SUBSECTOR_H
#define __SUBSECTOR_H

#include <stdint.h>

#include "segment.h"

#define SUBSECTOR_NUM_BYTES 4 // size on disk (in the lump)

class subsector
{
public:
  subsector();
  ~subsector();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_num_segments(void) const { return num_segments; }
  uint16_t get_first_segment_num(void) const { return first_segment_num; }

  void allocate_segments(void);
  void set_nth_segment(int n, segment const *_segment);

private:
  uint16_t num_segments;
  uint16_t first_segment_num;
  segment const **segments;
};

#endif