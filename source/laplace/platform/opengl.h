/*  laplace/platform/opengl.h
 *
 *      OpenGL utility.
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

#ifndef laplace_platform_opengl_h
#define laplace_platform_opengl_h

#include <string>
#include <vector>

#include "../../generated/gl/types.h"

namespace laplace::gl {
  using ptr_function = void(LAPLACE_GL_API *)();

  auto is_ok() -> bool;

  /*  Set required extensions.
   */
  void require_extensions(std::vector<std::string_view> extensions);

  /*  Load all the OpenGL functions.
   */
  auto init() -> bool;

  /*  Check if extension enabled.
   */
  auto has(std::string_view extension) -> bool;
}

#endif
