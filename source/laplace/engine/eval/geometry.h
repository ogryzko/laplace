/*  laplace/engine/eval/geometry.h
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

#ifndef laplace_engine_eval_geometry_h
#define laplace_engine_eval_geometry_h

#include "../defs.h"

namespace laplace::engine::eval {
  struct box {
    vec3i min = { safe_delta, safe_delta, safe_delta };
    vec3i max = { -safe_delta, -safe_delta, -safe_delta };
  };

  struct cylinder {
    vec3i  base   = { 0, 0, 0 };
    intval radius = -safe_delta;
    intval height = 0;
  };

  struct sphere {
    vec3i  center = { 0, 0, 0 };
    intval radius = -safe_delta;
  };

  using triangle = std::array<vec3i, 3>;
  using quad     = std::array<vec3i, 4>;
  using polygon  = std::vector<vec3i>;

  struct octree {
    box bounds;

    std::variant<std::vector<octree>, std::vector<triangle>> childs;
  };

  struct ray {
    vec3i base;
    vec3i direction;
  };

  struct plane {
    vec3i base;
    vec3i normal;
  };

  using ref_box      = box &;
  using ref_cylinder = cylinder &;
  using ref_sphere   = sphere &;
  using ref_triangle = triangle &;
  using ref_quad     = quad &;
  using ref_polygon  = polygon &;
  using ref_octree   = octree &;
  using ref_ray      = ray &;
  using ref_plane    = plane &;

  using cref_box      = const box &;
  using cref_cylinder = const cylinder &;
  using cref_sphere   = const sphere &;
  using cref_triangle = const triangle &;
  using cref_quad     = const quad &;
  using cref_polygon  = const polygon &;
  using cref_octree   = const octree &;
  using cref_ray      = const ray &;
  using cref_plane    = const plane &;

  using vtriangle = std::vector<triangle>;
  using vquad     = std::vector<quad>;
  using vpolygon  = std::vector<polygon>;
  using voctree   = std::vector<octree>;

  using ref_vtriangle = vtriangle &;
  using ref_vquad     = vquad &;
  using ref_vpolygon  = vpolygon &;
  using ref_voctree   = voctree &;

  using cref_vtriangle = const vtriangle &;
  using cref_vquad     = const vquad &;
  using cref_vpolygon  = const vpolygon &;
  using cref_voctree   = const voctree &;

  auto length(cref_vec3i v) -> intval;

  void append(ref_box a, cref_vec3i point);
  void append(ref_box a, cref_triangle b);
  void append(ref_box a, cref_quad b);
  void append(ref_box a, cref_polygon b);

  auto is_empty(cref_box a) -> bool;
  auto is_empty(cref_cylinder a) -> bool;
  auto is_empty(cref_sphere a) -> bool;
  auto is_empty(cref_octree a) -> bool;

  auto vertex_of(cref_box a, size_t index) -> vec3i;
  auto center_of(cref_box a) -> vec3i;
  auto center_of(cref_triangle a) -> vec3i;
  auto point_of(cref_ray a, intval t) -> vec3i;
  auto plane_of(cref_triangle a) -> plane;
  auto plane_of(cref_quad a) -> plane;
  auto plane_of(cref_polygon a) -> plane;
  auto plane_of(cref_box a, size_t index) -> plane;

  auto flat_center_of(cref_box a, size_t index) -> intval;
  auto flat_center_of(cref_triangle a, size_t index) -> intval;

  auto bounds_of(cref_cylinder a) -> box;
  auto bounds_of(cref_sphere a) -> box;
  auto bounds_of(cref_triangle a) -> box;
  auto bounds_of(cref_quad a) -> box;
  auto bounds_of(cref_polygon a) -> box;
  auto bounds_of(cref_vtriangle v) -> box;

  auto raw_normal(cref_triangle plane) -> vec3i;
  auto raw_normal(cref_vec3i p0, cref_vec3i p1, cref_vec3i p2)
      -> vec3i;
  auto orientation(cref_triangle plane, cref_vec3i point)
      -> intval;
  auto square_distance(cref_triangle plane, cref_vec3i point)
      -> intval;
  auto square_distance(cref_ray a, cref_vec3i point) -> intval;
  auto square_distance(cref_ray a, cref_ray b) -> intval;
  auto abs_square_distance(cref_triangle plane, cref_vec3i point)
      -> intval;
  auto contains_flat(cref_triangle a, cref_vec3i point) -> bool;
  auto contains_flat(cref_quad a, cref_vec3i point) -> bool;
  auto contains_flat(cref_polygon a, cref_vec3i point) -> bool;
  auto contains_flat(cref_cylinder a, cref_vec3i point) -> bool;

  auto contains(cref_box a, cref_vec3i point) -> bool;
  auto contains(cref_box a, cref_box b) -> bool;
  auto contains(cref_box a, cref_triangle b) -> bool;
  auto contains(cref_cylinder a, cref_vec3i point) -> bool;
  auto contains(cref_sphere a, cref_vec3i point) -> bool;
  auto contains(cref_octree a, cref_vec3i point) -> bool;

  auto intersects(cref_box a, cref_box b) -> bool;
  auto intersects(cref_box a, cref_cylinder b) -> bool;
  auto intersects(cref_box a, cref_sphere b) -> bool;
  auto intersects(cref_box a, cref_triangle b) -> bool;
  auto intersects(cref_box a, cref_octree b) -> bool;
  auto intersects(cref_cylinder a, cref_cylinder b) -> bool;
  auto intersects(cref_cylinder a, cref_sphere b) -> bool;
  auto intersects(cref_cylinder a, cref_triangle b) -> bool;
  auto intersects(cref_cylinder a, cref_octree b) -> bool;
  auto intersects(cref_sphere a, cref_sphere b) -> bool;
  auto intersects(cref_sphere a, cref_triangle b) -> bool;
  auto intersects(cref_sphere a, cref_octree b) -> bool;
  auto intersects(cref_triangle a, cref_triangle b) -> bool;
  auto intersects(cref_triangle a, cref_octree b) -> bool;
  auto intersects(cref_octree a, cref_octree b) -> bool;

  auto intersects(cref_ray a, cref_plane b) -> bool;
  auto intersects(cref_ray a, cref_triangle b) -> bool;
  auto intersects(cref_ray a, cref_quad b) -> bool;
  auto intersects(cref_ray a, cref_polygon b) -> bool;

  auto intersects(cref_ray a, cref_box b) -> bool;
  auto intersects(cref_ray a, cref_cylinder b) -> bool;
  auto intersects(cref_ray a, cref_sphere b) -> bool;
  auto intersects(cref_ray a, cref_octree b) -> bool;

  auto intersection(cref_ray a, cref_plane b) -> intval;
  auto intersection(cref_ray a, cref_triangle b) -> intval;
  auto intersection(cref_ray a, cref_quad b) -> intval;
  auto intersection(cref_ray a, cref_polygon b) -> intval;

  auto intersection(cref_ray a, cref_box b) -> intval;
  auto intersection(cref_ray a, cref_cylinder b) -> intval;
  auto intersection(cref_ray a, cref_sphere b) -> intval;
  auto intersection(cref_ray a, cref_octree b) -> intval;
}

#endif
