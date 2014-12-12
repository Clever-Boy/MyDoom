#ifndef __PROJECTOR_H
#define __PROJECTOR_H

#include <stdint.h>

#include "vector.h"

class projector
{
public:
  projector();

  void set_screen_size(uint16_t _screen_width, uint16_t _screen_height);

  float clip_horiz_angle_to_fov(float angle) const;
  int16_t get_horiz_fov_radius() const;
  int16_t project_horiz_angle_to_x(float angle) const;
  float unproject_x_to_horiz_angle(int16_t x) const;

  void set_left_clipping_vector( vertex *clip_l1, vertex *clip_l2) const;
  void set_right_clipping_vector(vertex *clip_r1, vertex *clip_r2) const;

private:
  uint16_t screen_width;
  uint16_t screen_height;
  float x_proj_scale;
};

void projector_tests(void);

#endif
