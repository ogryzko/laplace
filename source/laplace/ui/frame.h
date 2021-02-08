/*  laplace/ui/frame.h
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

#ifndef __laplace__ui_frame__
#define __laplace__ui_frame__

#include "../graphics/flat/framebuffer.h"
#include "context.h"
#include "widget.h"

namespace laplace::ui {
  class frame final : public widget {
  public:
    frame();
    ~frame() final = default;

    void set_context(ptr_context cont);

    void render() final;

  private:
    ptr_context                 m_context;
    graphics::flat::framebuffer m_buffer;
  };

  using ptr_frame = std::shared_ptr<frame>;
}

#endif
