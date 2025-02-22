/*  laplace/engine/protocol/session_response.h
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

#ifndef laplace_engine_protocol_session_response_h
#define laplace_engine_protocol_session_response_h

#include "../prime_impact.h"

namespace laplace::engine::protocol {
  class session_response : public prime_impact {
  public:
    enum encoding_offset : sl::index { n_port = 2, n_key = 4 };

    static constexpr sl::whole max_key_size = 1024;
    static constexpr uint16_t  id           = ids::session_response;

    using key_type = std::array<uint8_t, max_key_size>;

    ~session_response() final = default;

    constexpr session_response() {
      set_encoded_size(n_key);
    }

    constexpr session_response(uint16_t port, span_cbyte key) {
      m_port     = port;
      m_key_size = std::min<sl::whole>(key.size(), max_key_size);

      set_encoded_size(n_key + m_key_size);

      std::copy(key.begin(), key.begin() + m_key_size, m_key.begin());
    }

    static constexpr auto get_port(span_cbyte seq) {
      return serial::rd<uint16_t>(seq, n_port);
    }

    static constexpr auto get_key(span_cbyte seq) -> span_cbyte {
      if (seq.size() > n_key) {
        return { seq.begin() + n_key, seq.end() };
      }

      return {};
    }

    inline void encode_to(std::span<uint8_t> bytes) const final {
      serial::write_bytes(
          bytes, id, m_port,
          std::span<const uint8_t>(m_key.data(), m_key_size));
    }

    static constexpr auto scan(span_cbyte seq) -> bool {
      return seq.size() >= n_key && get_id(seq) == id;
    }

    static inline auto decode(span_cbyte seq) {
      return session_response { get_port(seq), get_key(seq) };
    }

  private:
    uint16_t  m_port     = {};
    sl::whole m_key_size = {};
    key_type  m_key      = {};
  };
}

#endif
