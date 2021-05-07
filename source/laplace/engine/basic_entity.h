/*  laplace/engine/basic_entity.h
 *
 *      Basic class for any gameplay object.
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

#ifndef laplace_engine_basic_entity_h
#define laplace_engine_basic_entity_h

#include "access/world.predef.h"
#include "basic_entity.predef.h"
#include "eval/shape.h"
#include "object/sets.h"
#include "world.predef.h"
#include <atomic>
#include <chrono>
#include <memory>
#include <shared_mutex>

namespace laplace::engine {
  /*  TODO
   *  Atomics, constexpr.
   */
  class basic_entity {
  public:
    class dummy_tag { };
    class proto_tag { };

    static constexpr auto lock_timeout = std::chrono::milliseconds(100);

    static constexpr auto dummy = dummy_tag {};
    static constexpr auto proto = proto_tag {};

    static constexpr uint64_t default_tick_period = 10;

    basic_entity(cref_entity en) noexcept;
    basic_entity(basic_entity &&en) noexcept;
    auto operator=(cref_entity en) noexcept -> ref_entity;
    auto operator=(basic_entity &&en) noexcept -> ref_entity;

    /*  Prototype initialization.
     */
    basic_entity(proto_tag = proto);

    /*  Dummy initialization.
     */
    basic_entity(dummy_tag);

    /*  Initialize dynamic entity.
     */
    basic_entity(uint64_t tick_period);

    virtual ~basic_entity() = default;

    /*  Set the Entity dynamic status.
     *  Thread-safe.
     */
    void set_dynamic(bool is_dynamic);

    /*  Set the Entity tick period.
     *  Thread-safe.
     */
    void set_tick_period(uint64_t tick_period);

    /*  Set the Entity clock current time.
     *  Thread-safe.
     */
    void set_clock(uint64_t clock_msec);

    /*  Set the Entity clock.
     *  Thread-safe.
     */
    void reset_clock();

    /*  Set the Entity id. Do not modify the
     *  id set by the World.
     */
    void set_id(size_t id);

    void set_world(ptr_world w);
    void reset_world();

    [[nodiscard]] auto index_of(size_t id) const -> size_t;
    [[nodiscard]] auto get_count() const -> size_t;

    [[nodiscard]] auto id_of(size_t index) const -> size_t;
    [[nodiscard]] auto scale_of(size_t index) const -> size_t;

    /*  Get a state value.
     *  Thread-safe.
     */
    [[nodiscard]] auto get(size_t index) -> int64_t;

    /*  Change a state value. It will apply
     *  calculated delta for the value. The actual
     *  value will change due adjusting.
     *  Thread-safe.
     */
    void set(size_t index, int64_t value);

    /*  Apply a state value delta.
     *  Thread-safe.
     */
    void apply_delta(size_t index, int64_t delta);

    /*  Adjust Entity new state.
     *  Thread-safe.
     */
    void adjust();

    /*  Perform an universal request.
     *  Thread-safe.
     */
    [[nodiscard]] auto request( //
        size_t     id,          //
        span_cbyte args = {}) -> vbyte;

    /*  Perform an universal modification.
     *  Thread-safe.
     */
    void modify(       //
        size_t     id, //
        span_cbyte args = {});

    /*  Dynamic Entity live loop.
     */
    virtual void tick(access::world w);

    /*  Decrement the clock timer. Returns true
     *  if the tick period has expired.
     *
     *  Thread-safe.
     */
    auto clock() -> bool;

    /*  Returns true if the Entity was changed.
     *  Thread-safe.
     */
    [[nodiscard]] auto is_changed() -> bool;

    /*  Returns true if the Entity is dynamic.
     *  Thread-safe.
     */
    [[nodiscard]] auto is_dynamic() -> bool;

    /*  Returns the tick period.
     *  Thread-safe.
     */
    [[nodiscard]] auto get_tick_period() -> uint64_t;

    /*  Returns the Entity id.
     */
    [[nodiscard]] auto get_id() const -> size_t;

    /*  Get a state value by id.
     *  Thread-safe.
     */
    [[nodiscard]] auto get_by_id(size_t id) -> int64_t;

  protected:
    /*  State values' indices in PRECISE order.
     */
    enum indices : size_t {
      n_is_dynamic = 0,
      n_tick_period,
    };

    struct sets_row {
      size_t  id    = id_undefined;
      int64_t scale = 0;
      int64_t value = 0;
      int64_t delta = 0;
    };

    using vsets_row      = std::vector<sets_row>;
    using cref_vsets_row = const vsets_row &;

    std::shared_timed_mutex m_lock;

    /*  Setup state values.
     */
    void setup_sets(cref_vsets_row sets);

    /*  Init state value.
     */
    void init(size_t index, int64_t value);

    /*  Get a state value without
     *  locking.
     */
    [[nodiscard]] auto locked_get(size_t index) const -> int64_t;

    /*  Get a state value by id
     *  without locking.
     */
    [[nodiscard]] auto locked_get_by_id(size_t id) const -> int64_t;

    void self_destruct(const access::world &w);
    void desync();

    /*  Universal request implementation.
     *
     *  Thread-safe methods not allowed
     *  from here due to the locking.
     */
    [[nodiscard]] virtual auto do_request( //
        size_t     id,                     //
        span_cbyte args) const -> vbyte;

    /*  Universal modification implementation.
     *
     *  Thread-safe methods not allowed
     *  from here due to the locking.
     */
    virtual void do_modify( //
        size_t     id,      //
        span_cbyte args);

  private:
    void assign(cref_entity en) noexcept;
    void assign(basic_entity &&en) noexcept;

    std::weak_ptr<world> m_world;

    vsets_row m_sets;
    uint64_t  m_clock = 0;

    size_t m_id         = id_undefined;
    bool   m_is_changed = false;
  };
}

#include "basic_entity.impl.h"

#endif
