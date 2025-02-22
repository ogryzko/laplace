/*  test/unittests/n_udp.test.cpp
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

#include "../../laplace/network/udp_node.h"
#include <gtest/gtest.h>
#include <thread>

namespace laplace::test {
  using network::udp_node, network::any_port, network::localhost,
      network::async;

  namespace this_thread = std::this_thread;

  TEST(network, udp_message) {
    constexpr sl::index test_count     = 3;
    constexpr sl::index test_threshold = 1;

    sl::index success = 0;

    for (sl::index i = 0; i < test_count; i++) {
      udp_node a;
      udp_node b(any_port);

      vbyte msg = { 1, 2, 3 };

      if (a.send_to(localhost, b.get_port(), msg) != msg.size()) {
        continue;
      }

      this_thread::yield();

      auto seq = b.receive(msg.size(), async);

      if (msg == seq)
        success++;
    }

    EXPECT_GE(success, test_threshold);
  }

  TEST(network, udp_echo) {
    constexpr sl::index test_count     = 3;
    constexpr sl::index test_threshold = 1;

    sl::index success = 0;

    for (sl::index i = 0; i < test_count; i++) {
      udp_node a;
      udp_node b(any_port);

      vbyte msg = { 1, 2, 3 };
      vbyte req = { 5 };

      if (a.send_to(localhost, b.get_port(), req) != req.size())
        continue;

      this_thread::yield();

      if (b.receive(req.size(), async) != req) {
        continue;
      }

      if (b.send_to(b.get_remote_address(), b.get_remote_port(),
                    msg) != msg.size()) {
        continue;
      }

      this_thread::yield();

      auto seq = a.receive(msg.size(), async);

      if (msg == seq)
        success++;
    }

    EXPECT_GE(success, test_threshold);
  }
}
