#ifndef __NODE_H
#define __NODE_H

#include <stdint.h>

#include "bbox.h"
#include "subsector.h"
#include "partition_line.h"
#include "projector.h"
#include "camera.h"
#include "clipped_segment_projections.h"
#include "vis_planes.h"

#define NODE_CHILD_NUM_MASK       0x7fff
#define NODE_CHILD_TYPE_MASK      0x8000
#define NODE_CHILD_TYPE_SUBSECTOR 0x8000
#define NODE_CHILD_TYPE_NODE      0x0000

class node; // forward declaration, so it can be used in node_child_link

class node_child_link
{
public:
  bbox       _bbox;
  uint16_t   child_type;
  uint16_t   child_num;
  node      *_node;
  subsector *_subsector;

  bool is_subsector() const { return (child_type == NODE_CHILD_TYPE_SUBSECTOR); }
  bool is_node() const      { return (child_type == NODE_CHILD_TYPE_NODE); }
};

#define NODE_NUM_BYTES 28 // size on disk (in the lump)

class node
{
public:
  node();
  ~node();

  bool read_from_lump_data(uint8_t const *lump_data);

  partition_line const *get_partition(void) const { return &partition; }
  node_child_link const *get_left(void) const { return &left; }
  node_child_link const *get_right(void) const { return &right; }

  void set_left_node(node *_node) { left._node = _node; }
  void set_right_node(node *_node) { right._node = _node; }
  void set_left_subsector(subsector *_subsector) { left._subsector = _subsector; }
  void set_right_subsector(subsector *_subsector) { right._subsector = _subsector; }

  void render_player_view(camera const *_camera,
                          clipped_segment_projections *clipped_seg_projs, 
                          vis_planes *vp, 
                          map_object * const map_objects[], int16_t num_map_objects, vis_map_objects *vmo) const;

  bool undrawn_columns_toward_bbox(bbox const *_bbox, clipped_segment_projections *clipped_seg_projs, camera const *_camera) const;

  subsector const *get_subsector_containing(vertex const *v) const;

  uint16_t node_num; // for debug printing

private:
  partition_line partition;
  node_child_link left;
  node_child_link right;
};

#endif
