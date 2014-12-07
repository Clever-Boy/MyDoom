#ifndef __LINEDEF_H
#define __LINEDEF_H

#include <stdint.h>

#include "vertex.h"
#include "sidedef.h"

#define LINEDEF_NUM_BYTES 14 // size on disk (in the lump)

#define LINEDEF_FLAGS_MASK_BLOCKS_PLAYERS_AND_MONSTERS	0x0001 // blocks players and monsters 
#define LINEDEF_FLAGS_MASK_BLOCKS_MONSTERS		0x0002 // blocks monsters 
#define LINEDEF_FLAGS_MASK_TWO_SIDED			0x0004 // two sided 
#define LINEDEF_FLAGS_MASK_UPPER_TEXTURE_IS_UNPEGGED	0x0008 // upper texture is unpegged 
#define LINEDEF_FLAGS_MASK_LOWER_TEXTURE_IS_UNPEGGED	0x0010 // lower texture is unpegged 
#define LINEDEF_FLAGS_MASK_SECRET			0x0020 // secret (shows as one-sided on automap), and 
							       // monsters cannot open if it is a door (type 1) 
#define LINEDEF_FLAGS_MASK_BLOCKS_SOUND			0x0040 // blocks sound 
#define LINEDEF_FLAGS_MASK_NEVER_ON_AUTOMAP		0x0080 // never shows on automap 
#define LINEDEF_FLAGS_MASK_ALWAYS_ON_AUTOMAP		0x0100 // always shows on automap

class linedef
{
public:
  linedef();
  ~linedef();

  bool read_from_lump_data(uint8_t const *lump_data);

  uint16_t get_start_vertex_num(void) const { return start_vertex_num; }
  uint16_t get_end_vertex_num(void) const { return end_vertex_num; }
  uint16_t get_flags(void) const { return flags; }
  uint16_t get_special_type(void) const { return special_type; }
  uint16_t get_sector_tag(void) const { return sector_tag; }
  uint16_t get_right_sidedef_num(void) const { return right_sidedef_num; }
  uint16_t get_left_sidedef_num(void) const { return left_sidedef_num; }

  void set_left_sidedef(sidedef const *_sidedef);
  void set_right_sidedef(sidedef const *_sidedef);
  void alloc_vertexes(void);
  void set_nth_vertex(int n, vertex const *v);

private:
  uint16_t start_vertex_num;
  uint16_t end_vertex_num;
  uint16_t flags;
  uint16_t special_type;
  uint16_t sector_tag;
  uint16_t right_sidedef_num;
  uint16_t left_sidedef_num;

  sidedef const *left_sidedef;
  sidedef const *right_sidedef;
  uint16_t num_vertexes;
  vertex const **vertexes;
};

#endif