/*  laplace/engine/eventorder.h
 *
 *      Trivial class that contains event order information.
 *      Allows to sort tree-structured events.
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

#ifndef laplace_engine_eventorder_h
#define laplace_engine_eventorder_h

#include "../core/defs.h"

namespace laplace::engine {
  class eventorder {
  public:
    /*  Maximum event tree depth.
     */
    static constexpr uint8_t max_depth = 16;

    static constexpr size_t tick = 0;
    static constexpr size_t root = 1;

    constexpr eventorder() = default;
    constexpr eventorder(size_t index);
    ~eventorder() = default;

    constexpr eventorder(const eventorder &) = default;
    constexpr eventorder(eventorder &&)      = default;
    constexpr auto operator                  =(const eventorder &)
        -> eventorder &                      = default;
    constexpr auto operator=(eventorder &&) -> eventorder & = default;

    /*  Spawn a child event.
     */
    [[nodiscard]] constexpr auto spawn(ref_uint child_count) const
        -> eventorder;

    [[nodiscard]] constexpr auto operator<(const eventorder &order) const
        -> bool;

    [[nodiscard]] constexpr auto get_index() const -> size_t;

  private:
    constexpr eventorder(const eventorder &parent, size_t child_index);

    std::array<size_t, max_depth> m_indices = { 0 };
    uint8_t                       m_size    = 0;
  };

  using cref_eventorder = const eventorder &;
}

#include "eventorder.impl.h"

#endif
