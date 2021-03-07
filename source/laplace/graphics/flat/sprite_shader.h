/*  laplace/graphics/flat/sprite_shader.h
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

#ifndef laplace_graphics_flat_sprite_shader_h
#define laplace_graphics_flat_sprite_shader_h

#include "../defs.h"
#include "../program.h"

namespace laplace::graphics::flat {
  class sprite_shader {
  public:
    struct vertex {
      vec2 position;
      vec2 texcoord;
    };

    sprite_shader(ref_istream vert, ref_istream frag);
    ~sprite_shader();

    void use();

    void set_position(cref_vec2 position);
    void set_scale(cref_vec2 scale);
    void set_texture(size_t id);

  private:
    int n_position;
    int n_scale;
    int n_texture;

    program m_program;
  };

  using ptr_sprite_shader = std::shared_ptr<sprite_shader>;
}

#endif
