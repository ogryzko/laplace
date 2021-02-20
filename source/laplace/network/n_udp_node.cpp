#include "udp_node.h"
#include "utils.h"

namespace laplace::network {
  using std::string_view, std::string;

  udp_node::udp_node() {
    init();
  }

  udp_node::udp_node(uint16_t port) {
    init();

    bind(port);
  }

  udp_node::~udp_node() {
    if (m_socket != INVALID_SOCKET) {
      ::closesocket(m_socket);
      m_socket = INVALID_SOCKET;
    }
  }

  void udp_node::bind(uint16_t port) {
    sockaddr_in name;
    memset(&name, 0, sizeof name);

    name.sin_family      = AF_INET;
    name.sin_port        = ::htons(port);
    name.sin_addr.s_addr = ::htonl(INADDR_ANY);

    auto status = ::bind(m_socket,
                         reinterpret_cast<const SOCKADDR *>(&name),
                         sizeof name);

    if (status == SOCKET_ERROR) {
      verb("UDP: bind failed (code %d).", socket_error());
      return;
    }

    if (port == any_port) {
      int len = sizeof name;

      if (::getsockname(m_socket, reinterpret_cast<sockaddr *>(&name),
                        &len) == SOCKET_ERROR) {
        verb("UDP: getsockname failed (code %d).", socket_error());
        ::closesocket(m_socket);
        m_socket = INVALID_SOCKET;
        return;
      }

      m_port = ::ntohs(name.sin_port);
    } else {
      m_port = port;
    }
  }

  auto udp_node::receive_to(uint8_t *p, size_t count, io_mode mode)
      -> size_t {
    size_t size = 0;

    if (m_socket != INVALID_SOCKET && (p != nullptr || count == 0)) {
      int len = sizeof m_remote;
      memset(&m_remote, 0, sizeof m_remote);

      auto addr    = reinterpret_cast<SOCKADDR *>(&m_remote);
      auto buf     = reinterpret_cast<char *>(p);
      bool is_sync = false;

      for (; size < count;) {
        auto part = clamp_chunk(count - size);

        auto n = ::recvfrom(m_socket, buf + size, part, 0, addr, &len);

        if (n != SOCKET_ERROR) {
          size += n;
        } else if (socket_error() == socket_msgsize()) {
          verb("UDP: recvfrom failed, buffer too small (EMSGSIZE).");
          break;
        } else if (socket_error() == socket_connreset()) {
          verb("UDP: recvfrom failed, connection was forcibly closed "
               "by the remote host (ECONNRESET).");
          break;
        } else if (socket_error() != socket_wouldblock()) {
          verb("UDP: recvfrom failed (code %d).", socket_error());
          break;
        } else if (mode == sync) {
          is_sync = set_mode(m_socket, sync);

          if (!is_sync) {
            verb("UDP: ioctlsocket failed (code %d).", socket_error());
            break;
          }
        } else
          break;
      }

      if (is_sync) {
        if (!set_mode(m_socket, async)) {
          verb("UDP: ioctlsocket failed (code %d).", socket_error());
        }
      }
    }

    return size;
  }

  auto udp_node::receive(size_t count, io_mode mode) -> vbyte {
    vbyte seq;

    if (m_socket != INVALID_SOCKET) {
      seq.resize(count);
      seq.resize(receive_to(seq.data(), count, mode));
    }

    return seq;
  }

  auto udp_node::send_to(string_view address, uint16_t port,
                         cref_vbyte seq) -> size_t {
    size_t result = 0;

    sockaddr_in name;
    memset(&name, 0, sizeof name);

    name.sin_family = AF_INET;
    name.sin_port   = ::htons(port);

    const auto status = ::inet_pton(
        AF_INET, address.data(), &name.sin_addr.s_addr);

    if (status != 1) {
      verb("UDP: inet_pton failed (code %d).", socket_error());
    } else {
      result = send_internal(name, seq);
    }

    return result;
  }

  auto udp_node::get_port() const -> uint16_t {
    return m_port;
  }

  auto udp_node::get_remote_address() const -> string {
    return to_string(reinterpret_cast<const sockaddr &>(m_remote));
  }

  auto udp_node::get_remote_port() const -> uint16_t {
    return ::ntohs(m_remote.sin_port);
  }

  void udp_node::init() {
    memset(&m_remote, 0, sizeof m_remote);

    m_socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (m_socket == INVALID_SOCKET) {
      verb("UDP: socket failed (code %d).", socket_error());
      return;
    }

    if (!set_mode(m_socket, async)) {
      verb("UDP: ioctlsocket failed (code %d).", socket_error());
    }
  }

  auto udp_node::send_internal(const sockaddr_in &name, cref_vbyte seq)
      -> size_t {
    size_t count = 0;

    if (m_socket != INVALID_SOCKET) {
      auto buf     = reinterpret_cast<const char *>(seq.data());
      auto addr    = reinterpret_cast<const SOCKADDR *>(&name);
      bool is_sync = false;

      for (; count < seq.size();) {
        auto part = clamp_chunk(seq.size() - count);

        auto n = ::sendto(
            m_socket, buf + count, part, 0, addr, sizeof name);

        if (n != SOCKET_ERROR) {
          count += n;
        } else if (socket_error() != socket_wouldblock()) {
          verb("UDP: sendto failed (code %d).", socket_error());
          break;
        } else {
          is_sync = set_mode(m_socket, sync);

          if (!is_sync) {
            verb("UDP: ioctlsocket failed (code %d).", socket_error());
            break;
          }
        }
      }

      if (is_sync) {
        if (!set_mode(m_socket, async)) {
          verb("UDP: ioctlsocket failed (code %d).", socket_error());
        }
      }
    }

    return count;
  }
}
