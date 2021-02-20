/*  apps/quadwar/sets.h
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

#ifndef __quadwar__sets__
#define __quadwar__sets__

#include "../../laplace/engine/object/sets.h"

namespace quadwar_app::sets {
  using namespace laplace::engine::object::sets;

  enum set_id : size_t {
    player_name = _native_count,

    root_is_changed,
    root_is_launched,
    root_slot_count,
    root_slot_get,
    root_slot_create,
    root_slot_remove,
    root_launch,

    game_clock_time,

    _count
  };
}

#endif
