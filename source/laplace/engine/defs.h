/*  laplace/engine/defs.h
 *
 *      Basic engine definitions. All the gameplay values are
 *      fixed-point numbers.
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

#ifndef laplace_engine_defs_h
#define laplace_engine_defs_h

#include "../math/vector.h"
#include <array>
#include <variant>
#include <vector>

namespace laplace::engine {
  using intval = int64_t;

  constexpr intval epsilon    = 1;
  constexpr intval safe_delta = 2;
  constexpr intval intval_max = std::numeric_limits<intval>::max();
  constexpr intval infinity   = intval_max >> 4;
  constexpr intval safe_limit = intval_max >> 2;

  constexpr uint64_t time_undefined = -1;
  constexpr size_t   id_undefined   = -1;

  using vec2i = math::vector<2, intval>;
  using vec3i = math::vector<3, intval>;
  using vec4i = math::vector<4, intval>;

  using ref_vec2i = vec2i &;
  using ref_vec3i = vec3i &;
  using ref_vec4i = vec4i &;

  using cref_vec2i = const vec2i &;
  using cref_vec3i = const vec3i &;
  using cref_vec4i = const vec4i &;
}

#endif
