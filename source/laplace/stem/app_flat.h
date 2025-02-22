/*  laplace/stem/app_flat.h
 *
 *      Base class for UI and 2D graphics application.
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

#ifndef laplace_stem_app_flat_h
#define laplace_stem_app_flat_h

#include "../ui/frame.h"
#include "application.h"

namespace laplace::stem {
  class app_flat : public application {
  public:
    static constexpr graphics::vec4 clear_color = { .1f, .09f, .12f,
                                                    1.f };

    app_flat(int argc, char **argv, core::cref_family def_cfg);
    ~app_flat() override;

  protected:
    void init() override;
    void cleanup() override;
    void update(uint64_t delta_msec) override;
    void render() override;
    void adjust_layout(sl::whole width, sl::whole height) override;

    ui::ptr_frame m_ui;
  };
}

#endif
