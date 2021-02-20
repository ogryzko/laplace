/*  apps/quadwar/session.h
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

#ifndef __quadwar__session__
#define __quadwar__session__

#include "../../laplace/network/defs.h"
#include "../../laplace/network/server.h"
#include "ids.h"
#include "lobby.h"
#include "qw_factory.h"

namespace quadwar_app {
  using namespace laplace;
  using namespace engine;

  class session {
  public:
    using event_done = std::function<void()>;
    using event_quit = std::function<void()>;

    static constexpr uint16_t allowed_commands[] = {
      ids::public_key,   ids::request_events, ids::ping_request,
      ids::client_enter, ids::client_leave,   ids::client_ready,
      ids::slot_create,  ids::slot_remove,    ids::player_name,
      ids::server_launch
    };

    static constexpr auto     default_server_ip = "127.0.0.1";
    static constexpr uint16_t default_port      = network::any_port;

    session();
    ~session() = default;

    void on_done(event_done ev);
    void on_quit(event_quit ev);

    void tick(size_t delta_msec);

    void attach_to(ui::ptr_widget w);
    void adjust_layout(int width, int height);

    void set_server_ip(std::string_view server_ip);
    void set_server_port(uint16_t port);
    void set_game_name(std::u8string_view game_name);
    void set_player_name(std::u8string_view player_name);
    void set_map_size(size_t map_size);
    void set_player_count(size_t player_count);
    void set_unit_count(size_t unit_count);

    void create();
    void join();

  private:
    void update_lobby();

    event_done m_on_done;
    event_quit m_on_quit;

    /*  Local actor id.
     */
    size_t m_id_actor = id_undefined;

    ptr_world m_world;

    std::string   m_server_ip   = default_server_ip;
    uint16_t      m_server_port = default_port;
    std::u8string m_game_name;
    std::u8string m_player_name;
    size_t        m_map_size     = 0;
    size_t        m_player_count = 0;
    size_t        m_unit_count   = 0;

    network::ptr_server m_server;

    lobby m_lobby;
  };

  using ptr_session = std::shared_ptr<session>;
}

#endif
