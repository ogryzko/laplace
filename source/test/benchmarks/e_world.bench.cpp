/*  test/benchmarks/e_world.bench.cpp
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

#include "../../laplace/engine/access/world.h"
#include "../../laplace/engine/world.h"
#include <benchmark/benchmark.h>

namespace laplace::bench {
  using std::make_shared, engine::basic_entity, engine::world,
      engine::id_undefined;

  namespace access = engine::access;
  namespace sets   = engine::object::sets;

  class my_entity : public basic_entity {
  public:
    my_entity() : basic_entity(true) {

      setup_sets({ { sets::debug_value, 0, 0 } });
      n_value = index_of(sets::debug_value);
    }

    ~my_entity() override = default;

    void tick(access::world) override {
      apply_delta(n_value, 1);
    }

  private:
    size_t n_value = 0;
  };

  static void engine_world_startup(benchmark::State &state) {
    for (auto _ : state) {
      auto a = make_shared<world>();
      a->set_thread_count(32);
    }
  }

  BENCHMARK(engine_world_startup);

  static void engine_world_single_thread(benchmark::State &state) {
    auto a = make_shared<world>();
    auto e = make_shared<my_entity>();

    a->set_thread_count(0);
    a->spawn(e, id_undefined);

    for (auto _ : state) {
      a->tick(100);

      auto value = e->get(e->index_of(sets::debug_value));

      benchmark::DoNotOptimize(value);
    }
  }

  BENCHMARK(engine_world_single_thread);

  static void engine_world_multithreading(benchmark::State &state) {
    auto a = make_shared<world>();
    auto e = make_shared<my_entity>();

    a->set_thread_count(32);
    a->spawn(e, id_undefined);

    for (auto _ : state) {
      a->tick(100);

      auto value = e->get(e->index_of(sets::debug_value));

      benchmark::DoNotOptimize(value);
    }
  }

  BENCHMARK(engine_world_multithreading);
}
