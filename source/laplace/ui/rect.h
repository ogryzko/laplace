/*  laplace/ui/rect.h
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

#ifndef laplace_ui_rect_h
#define laplace_ui_rect_h

#include "../core/slib.h"

namespace laplace::ui {
  struct rect {
    sl::index x      = 0;
    sl::index y      = 0;
    sl::whole width  = 0;
    sl::whole height = 0;
  };

  struct rectf {
    float x      = 0.f;
    float y      = 0.f;
    float width  = 0.f;
    float height = 0.f;
  };

  using cref_rect  = const rect &;
  using cref_rectf = const rectf &;

  auto compare(cref_rect a, cref_rect b) -> bool;
  auto contains(cref_rect a, sl::index x, sl::index y) -> bool;
  auto contains(cref_rect a, cref_rect b) -> bool;
  auto intersects(cref_rect a, cref_rect b) -> bool;

  auto to_rectf(cref_rect a) -> rectf;
  auto to_rect(cref_rectf a) -> rect;

  inline auto operator==(cref_rect a, cref_rect b) -> bool {
    return compare(a, b);
  }

  inline auto operator!=(cref_rect a, cref_rect b) -> bool {
    return !compare(a, b);
  }
}

#endif
