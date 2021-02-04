/*  laplace/unittests/e_server.test.cpp
 *
 *      LLVM libFuzzer entry.
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

#include "../../laplace/engine/host.h"
#include "../../laplace/engine/object/sets.h"
#include "../../laplace/engine/protocol/debug.h"
#include "../../laplace/engine/protocol/ids.h"
#include "../../laplace/engine/remote.h"
#include <gtest/gtest.h>
#include <thread>

using namespace laplace;
using namespace engine;
using namespace object;
using namespace protocol;
using namespace std;

TEST(laplace_engine, server_echo) {
  constexpr auto address = "127.0.0.1";

  auto my_host = make_shared<host>();
  auto client  = make_shared<remote>();

  my_host->set_factory(make_shared<basic_factory>());
  client->set_factory(make_shared<basic_factory>());

  uint16_t allowed_commands[] = { ids::debug,
                                  ids::client_enter };

  my_host->set_allowed_commands(allowed_commands);
  my_host->listen();

  client->connect(address, my_host->get_port());

  int64_t test_value = 12367;

  client->tick(0);
  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();

  client->queue(encode(debug(test_value)));
  client->tick(0);

  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();
  client->tick(0);
  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();
  client->tick(0);

  int64_t echo_value = 0;

  if (auto w = client->get_world(); w) {
    if (auto root = w->get_root(); root) {
      root->adjust();

      echo_value = root->get(root->index_of(sets::debug_value));
    }
  }

  EXPECT_EQ(echo_value, test_value);
}

TEST(laplace_engine, server_encryption) {
  constexpr auto address = "127.0.0.1";

  auto my_host = make_shared<host>();
  auto client  = make_shared<remote>();

  my_host->set_factory(make_shared<basic_factory>());
  client->set_factory(make_shared<basic_factory>());

  uint16_t allowed_commands[] = { ids::debug, ids::client_enter,
                                  ids::public_key };

  my_host->set_allowed_commands(allowed_commands);
  my_host->listen();

  client->connect(address, my_host->get_port());

  int64_t test_value = 12367;

  client->tick(0);
  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();

  client->queue(encode(debug(test_value)));
  client->tick(0);

  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();
  client->tick(0);
  this_thread::yield();
  my_host->tick(0);
  this_thread::yield();
  client->tick(0);

  int64_t echo_value = 0;

  if (auto w = client->get_world(); w) {
    if (auto root = w->get_root(); root) {
      root->adjust();

      echo_value = root->get(root->index_of(sets::debug_value));
    }
  }

  EXPECT_EQ(echo_value, test_value);
}
