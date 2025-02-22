/*  laplace/engine/access/world.impl.h
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

#ifndef laplace_engine_access_world_impl_h
#define laplace_engine_access_world_impl_h

namespace laplace::engine::access {
  template <typename dist_>
  inline auto world::random(dist_ &dist) const ->
      typename dist_::result_type {

    if (is_allowed(sync, m_mode)) {
      return dist(get_random_engine());
    }

    return {};
  }
}

#endif
