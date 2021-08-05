/*  apps/quadwar/object/unit.h
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

#ifndef quadwar_object_unit_h
#define quadwar_object_unit_h

#include "../../../laplace/engine/basic_entity.h"
#include "../view/defs.h"
#include "defs.h"

namespace quadwar_app::object {
  class unit : public engine::basic_entity, helper {
  public:
    enum state : sl::index { s_stand, s_move, s_order_move };

    static const sl::whole default_waypoint_count;

    static const engine::intval default_health;
    static const engine::intval default_radius;
    static const engine::intval default_collision_radius;
    static const engine::intval default_movement_speed;

    unit();
    ~unit() override = default;

    void tick(engine::access::world w) override;

    static auto spawn_start_units(world w, sl::whole unit_count)
        -> std::vector<sl::index>;

    static void place_footprint(world w, sl::index id_unit);

    static void order_move(world w, sl::index id_actor,
                           sl::index id_unit, engine::vec2i target);

    [[nodiscard]] static auto get_actor(entity en) -> sl::index;
    [[nodiscard]] static auto get_color(entity en) -> sl::index;
    [[nodiscard]] static auto get_x(entity en) -> engine::intval;
    [[nodiscard]] static auto get_y(entity en) -> engine::intval;
    [[nodiscard]] static auto get_position(entity en) -> engine::vec2i;
    [[nodiscard]] static auto get_radius(entity en) -> engine::intval;
    [[nodiscard]] static auto get_health(entity en) -> engine::intval;

    [[nodiscard]] static auto get_position_scaled(entity en)
        -> view::vec2;

    [[nodiscard]] static auto get_radius_scaled(entity en)
        -> view::real;

  protected:
    unit(proto_tag);

  private:
    struct footprint_data {
      engine::vec2z      size;
      sl::vector<int8_t> bytes;
    };

    [[nodiscard]] static auto make_footprint(sl::whole radius)
        -> footprint_data;

    void do_move(world w);
    void do_order_move(world w);
    void do_next_waypoint();

    static unit m_proto;

    static sl::index n_state;
    static sl::index n_health;
    static sl::index n_radius;
    static sl::index n_collision_radius;
    static sl::index n_movement_speed;
    static sl::index n_actor;
    static sl::index n_color;
    static sl::index n_x;
    static sl::index n_y;
    static sl::index n_move_x;
    static sl::index n_move_y;
    static sl::index n_speed_remains;
    static sl::index n_target_x;
    static sl::index n_target_y;
    static sl::index n_waypoint_index;
    static sl::index n_waypoint_count;
  };
}

#endif
