/*  apps/quadwar/object/sets.h
 *
 *  Copyright (c) 2021 Mitya Selivanov
 *
 *  This file is part of the Laplace project.
 *
 *  Laplace is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 *  the MIT License for more details.
 */

#ifndef quadwar_object_sets_h
#define quadwar_object_sets_h

#include "../../../laplace/engine/object/sets.h"

namespace quadwar_app::object::sets {
  using namespace laplace::engine::object::sets;

  enum set_id : size_t {
    state_version = _native_count,

    player_name,

    root_is_loading,
    root_is_launched,
    root_slot_count,
    root_slot_get,
    root_slot_create,
    root_slot_remove,
    root_launch,
    root_landscape,

    game_clock_time,

    land_width,
    land_height,
    land_set_size,
    land_get_tile,
    land_set_tile,
    land_set_tiles,
    land_get_tiles,
    land_get_start_loc,
    land_set_start_loc,
    land_get_start_locs,
    land_set_start_locs,

    _count
  };
}

#endif
