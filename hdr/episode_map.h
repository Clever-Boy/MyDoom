#ifndef __EPISODE_MAP_H
#define __EPISODE_MAP_H

#include "wad_file.h"
#include "wad_lump.h"

#include "thing_instance.h"
#include "map_object.h"
#include "linedef.h"
#include "sidedef.h"
#include "vertex.h"
#include "segment.h"
#include "subsector.h"
#include "node.h"
#include "sector.h"
#include "reject_table.h"
#include "block_map.h"
#include "overhead_map.h"
#include "camera.h"
#include "clipped_segment_projections.h"
#include "vis_planes.h"
#include "vis_map_objects.h"
#include "actor.h"

class episode_map
{
public:
  episode_map();
  ~episode_map();

  bool read_from_lump(wad_file const *wad, wad_lump const *lump);

  char const *get_name(void) const { return name; }
  int get_num_thing_instances(void) const { return num_thing_instances; }
  thing_instance const *get_nth_thing_instance(int n) const { return &thing_instances[n]; }

  void draw_overhead_map(overhead_map *omap) const;

  void render_player_view(camera const *_camera,
                          clipped_segment_projections *clipped_seg_projs, 
                          vis_planes *vp, 
                          map_object * const map_objects[], int num_map_objects, vis_map_objects *vt) const;

  bool can_move(vertex const *old_position, vertex const *new_position, float radius) const;
  int16_t get_floor_height_at(vertex const *position) const;

  void direct_actors(void);

  node *root_node(void) const { return &nodes[num_nodes-1]; } // FIXME: it'd probably be better to hide this and expose the needed methods

private:
  char *name;

  int num_thing_instances;
  thing_instance *thing_instances;

  int num_linedefs;
  linedef *linedefs;

  int num_sidedefs;
  sidedef *sidedefs;

  int num_vertexes;
  vertex *vertexes;

  int num_segments;
  wad_segment *segments;

  int num_subsectors;
  subsector *subsectors;

  int num_nodes;
  node *nodes;

  int num_sectors;
  sector *sectors;

  reject_table reject_tbl;
  block_map    _block_map;

  #define MAX_NUM_ACTORS 100
  actor *actors[MAX_NUM_ACTORS];
  int num_actors;

  bool read_thing_instances(wad_lump const *lump);
  bool read_linedefs(wad_lump const *lump);
  bool read_sidedefs(wad_lump const *lump);
  bool read_vertexes(wad_lump const *lump);
  bool read_segments(wad_lump const *lump);
  bool read_subsectors(wad_lump const *lump);
  bool read_nodes(wad_lump const *lump);
  bool read_sectors(wad_lump const *lump);

  void link_nodes_to_children(void);
  void link_sectors_to_flats(void);
  void link_subsectors_to_segments(void);
  void link_segments_to_children(void);
  void link_linedefs_to_children(void);
  void link_sidedefs_to_children(void);
  void link_blocks_to_children(void);

  void add_actor(actor *a);
};

#endif
