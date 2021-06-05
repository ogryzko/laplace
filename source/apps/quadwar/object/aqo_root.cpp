/*  apps/quadwar/object/aqo_root.cpp
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

#include "../../../laplace/core/serial.h"
#include "root.h"
#include <algorithm>

namespace quadwar_app::object {
  using std::lower_bound, std::unique_lock, std::shared_lock,
      std::span, engine::id_undefined;

  sl::index root::n_version     = {};
  sl::index root::n_is_loading  = {};
  sl::index root::n_is_launched = {};
  sl::index root::n_slot_count  = {};
  sl::index root::n_unit_count  = {};
  sl::index root::n_landscape   = {};
  sl::index root::n_pathmap     = {};

  root root::m_proto(root::proto);

  root::root(root::proto_tag) {
    setup_sets({ { .id = sets::state_version, .scale = 1 },
                 { .id = sets::root_is_loading, .scale = 1 },
                 { .id = sets::root_is_launched, .scale = 1 },
                 { .id = sets::root_slot_count, .scale = 1 },
                 { .id = sets::root_unit_count, .scale = 1 },
                 { .id = sets::root_landscape, .value = -1 },
                 { .id = sets::root_pathmap, .value = -1 } });

    n_version     = index_of(sets::state_version);
    n_is_loading  = index_of(sets::root_is_loading);
    n_is_launched = index_of(sets::root_is_launched);
    n_slot_count  = index_of(sets::root_slot_count);
    n_unit_count  = index_of(sets::root_unit_count);
    n_landscape   = index_of(sets::root_landscape);
    n_pathmap     = index_of(sets::root_pathmap);
  }

  root::root() : basic_entity(dummy) {
    *this = m_proto;
  }

  void root::slot_create(entity en, sl::index id_actor) {

    if (id_actor == id_undefined) {
      error_("Invalid actor id.", __FUNCTION__);
      return;
    }

    en.modify(sets::root_slot_create, serial::pack_to_array(id_actor));
  }

  void root::slot_remove(entity en, sl::index id_actor) {

    if (id_actor == id_undefined) {
      error_("Invalid actor id.", __FUNCTION__);
      return;
    }

    en.modify(sets::root_slot_remove, serial::pack_to_array(id_actor));
  }

  void root::unit_create(entity en, sl::index id_unit) {

    if (id_unit == id_undefined) {
      error_("Invalid unit id.", __FUNCTION__);
      return;
    }

    en.modify(sets::root_unit_create, serial::pack_to_array(id_unit));
  }

  void root::unit_remove(entity en, sl::index id_unit) {

    if (id_unit == id_undefined) {
      error_("Invalid unit id.", __FUNCTION__);
      return;
    }

    en.modify(sets::root_unit_remove, serial::pack_to_array(id_unit));
  }

  void root::loading(entity en) {
    en.apply_delta(n_version, 1);
    en.set(n_is_loading, 1);
    en.adjust();
  }

  void root::launch(entity en) {
    en.modify(sets::root_launch);
  }

  void root::status_changed(entity en) {
    en.apply_delta(n_version, 1);
    en.adjust();
  }

  void root::set_landscape(entity en, sl::index id_landscape) {
    en.set(n_landscape, static_cast<int64_t>(id_landscape));
  }

  void root::set_pathmap(entity en, sl::index id_pathmap) {
    en.set(n_pathmap, static_cast<int64_t>(id_pathmap));
  }

  auto root::get_version(entity en) -> sl::index {
    return static_cast<sl::index>(en.get(n_version));
  }

  auto root::is_loading(entity en) -> bool {
    return en.get(n_is_loading) > 0;
  }

  auto root::is_launched(entity en) -> bool {
    return en.get(n_is_launched) > 0;
  }

  auto root::get_slot_count(entity en) -> sl::whole {
    return static_cast<sl::index>(en.get(n_slot_count));
  }

  auto root::get_slot(entity en, sl::index index) -> sl::index {

    const auto result = en.request(
        sets::root_slot_get, serial::pack_to_array(index));

    return serial::rd<sl::index>(result, 0);
  }

  auto root::get_unit_count(entity en) -> sl::whole {
    return static_cast<sl::index>(en.get(n_unit_count));
  }

  auto root::get_unit(entity en, sl::index index) -> sl::index {
    const auto result = en.request(
        sets::root_unit_get, serial::pack_to_array(index));

    return serial::rd<sl::index>(result, 0);
  }

  auto root::get_all_units(entity en) -> sl::vector<sl::index> {
    const auto result = en.request(sets::root_unit_get_all);

    auto units = sl::vector<sl::index>(result.size() /
                                       sizeof(sl::index));

    for (auto i = sl::index {}; i < units.size(); i++) {
      units[i] = serial::rd<sl::index>(result, i * sizeof(sl::index));
    }

    return units;
  }

  auto root::get_landscape(entity en) -> sl::index {
    return static_cast<sl::index>(en.get(n_landscape, -1));
  }

  auto root::get_pathmap(entity en) -> sl::index {
    return static_cast<sl::index>(en.get(n_pathmap, -1));
  }

  auto root::do_request(sl::index id, span_cbyte args) const -> vbyte {

    switch (id) {
      case sets::root_slot_get: {
        const auto index = serial::rd<sl::index>(args, 0);

        if (index < m_slots.size()) {
          return serial::pack_to_bytes(m_slots[index]);
        }
      } break;

      case sets::root_unit_get: {
        const auto index = serial::rd<sl::index>(args, 0);

        if (index < m_units.size()) {
          return serial::pack_to_bytes(m_units[index]);
        }
      } break;

      case sets::root_unit_get_all: {
        return serial::pack_to_bytes(span<const sl::index>(m_units));
      } break;
    }

    return {};
  }

  void root::do_modify(sl::index id, span_cbyte args) {

    switch (id) {
      case sets::root_slot_create:
        do_slot_create(serial::rd<sl::index>(args, 0));
        break;

      case sets::root_slot_remove:
        do_slot_remove(serial::rd<sl::index>(args, 0));
        break;

      case sets::root_unit_create:
        do_unit_create(serial::rd<sl::index>(args, 0));
        break;

      case sets::root_unit_remove:
        do_unit_remove(serial::rd<sl::index>(args, 0));
        break;

      case sets::root_launch: do_launch(); break;
    }
  }

  void root::do_slot_create(const sl::index id_actor) {
    const auto it = lower_bound(
        m_slots.begin(), m_slots.end(), id_actor);

    m_slots.emplace(it, id_actor);

    init(n_version, locked_get(n_version) + 1);
    init(n_slot_count, static_cast<int64_t>(m_slots.size()));
  }

  void root::do_slot_remove(const sl::index id_actor) {
    const auto it = lower_bound(
        m_slots.begin(), m_slots.end(), id_actor);

    if (it != m_slots.end() && *it == id_actor)
      m_slots.erase(it);

    init(n_version, locked_get(n_version) + 1);
    init(n_slot_count, static_cast<int64_t>(m_slots.size()));
  }

  void root::do_unit_create(const sl::index id_unit) {
    const auto it = lower_bound(
        m_units.begin(), m_units.end(), id_unit);
    m_units.emplace(it, id_unit);
    init(n_unit_count, static_cast<int64_t>(m_units.size()));
  }

  void root::do_unit_remove(const sl::index id_unit) {
    const auto it = lower_bound(
        m_units.begin(), m_units.end(), id_unit);
    if (it != m_units.end() && *it == id_unit)
      m_units.erase(it);
    init(n_unit_count, static_cast<int64_t>(m_units.size()));
  }

  void root::do_launch() {
    if (locked_get(n_is_launched) <= 0) {
      verb(R"(
 ************************************
 *                                  *
 *           L A U N C H            *
 *                                  *
 ************************************
)");

      init(n_version, locked_get(n_version) + 1);
      init(n_is_launched, 1);
    }
  }
}
