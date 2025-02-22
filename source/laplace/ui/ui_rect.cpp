/*  laplace/ui/ui_rect.cpp
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

#include "rect.h"

#include <cmath>

namespace laplace::ui {
  auto compare(cref_rect a, cref_rect b) -> bool {
    if (a.x != b.x || a.y != b.y)
      return false;

    if ((a.width > 0) != (b.width > 0))
      return false;

    if ((a.height > 0) != (b.height > 0))
      return false;

    if (a.width >= 0 && a.width != b.width)
      return false;

    if (a.height >= 0 && a.height != b.height)
      return false;

    return true;
  }

  auto contains(cref_rect a, sl::index x, sl::index y) -> bool {
    return x >= a.x && x < a.x + a.width && y >= a.y &&
           y < a.y + a.height;
  }

  auto contains(cref_rect a, cref_rect b) -> bool {
    return b.x >= a.x && b.x + b.width <= a.x + a.width &&
           b.y >= a.y && b.y + b.height <= a.y + a.height;
  }

  auto intersects(cref_rect a, cref_rect b) -> bool {
    return a.x < b.x + b.width && b.x < a.x + a.width &&
           a.y < b.y + b.height && b.y < a.y + a.height;
  }

  auto to_rectf(cref_rect a) -> rectf {
    return { .x      = static_cast<float>(a.x),
             .y      = static_cast<float>(a.y),
             .width  = static_cast<float>(a.width),
             .height = static_cast<float>(a.height) };
  }

  auto to_rect(cref_rectf a) -> rect {
    const auto x0 = static_cast<sl::index>(round(a.x));
    const auto y0 = static_cast<sl::index>(round(a.y));
    const auto x1 = static_cast<sl::index>(round(a.x + a.width));
    const auto y1 = static_cast<sl::index>(round(a.y + a.height));

    return { .x = x0, .y = y0, .width = x1 - x0, .height = y1 - y0 };
  }
}
