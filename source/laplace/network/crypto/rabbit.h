/*  laplace/network/crypto/rabbit.h
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

#ifndef laplace_network_crypto_rabbit_h
#define laplace_network_crypto_rabbit_h

#include "stream_cipher.h"

#include <wolfssl/options.h>

#include <wolfssl/wolfcrypt/rabbit.h>

#ifdef min
#  undef min
#endif

#ifdef max
#  undef max
#endif

namespace laplace::network::crypto {
  class rabbit : public stream_cipher {
  protected:
    ~rabbit() override = default;

    auto setup() -> bool override;

    auto do_encrypt(span_cbyte src, std::span<uint8_t> dst)
        -> bool override;

    auto do_decrypt(span_cbyte src, std::span<uint8_t> dst)
        -> bool override;

    auto rewind_decryption() -> bool override;

  private:
    static const sl::whole key_size;
    static const sl::whole key_extra;

    Rabbit m_encrypt = { 0 };
    Rabbit m_decrypt = { 0 };
    Rabbit m_origin  = { 0 };
  };
}

#endif
