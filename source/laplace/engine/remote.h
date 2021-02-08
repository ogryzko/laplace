/*  laplace/engine/remote.h
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

#ifndef __laplace__engine_remote__
#define __laplace__engine_remote__

#include "dh_rabbit.h"
#include "udp_server.h"

namespace laplace::engine {
  /*  Remote server.
   */
  class remote final : public udp_server {
  public:
    ~remote() final;

    void set_port(uint16_t port);

    void connect(std::string_view host_address,
                 uint16_t         host_port);

    void queue(cref_vbyte seq) final;
    void tick(size_t delta_msec) final;

    auto is_connected() -> bool;
    auto get_port() const -> uint16_t;

    template <typename impact_, typename... args_>
    inline void queue(args_... args) {
      this->queue(encode(impact_(args...)));
    }

  private:
    void cleanup();

    void receive_events();
    void perform_queue();
    void send_events();
    void update_world(size_t delta_msec);

    void receive_chunks();
    void process_buffer();
    void perform_event(cref_vbyte seq);
    auto convert_delta(size_t delta_msec) -> uint64_t;
    void send_event(cref_vbyte seq);
    void send_chunk();

    void add_event(cref_vbyte seq);
    auto perform_control(cref_vbyte seq) -> bool;
    auto adjust_overtake(uint64_t time) -> uint64_t;

    event_queue m_local_queue;
    event_queue m_queue;

    uint64_t m_time_msec  = 0;
    uint64_t m_time_limit = 0;

    /*  Networking.
     */

    std::string m_host_address;
    uint16_t    m_host_port   = network::any_port;
    uint16_t    m_client_port = network::any_port;
    dh_rabbit   m_cipher;
    vbyte       m_client_buffer;
    vbyte       m_chunks;

    std::unique_ptr<network::udp_node> m_node;
  };
}

#endif
