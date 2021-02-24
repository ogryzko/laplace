/*  laplace/network/crypto/prime.h
 *
 *    "Additional Diffie-Hellman Groups for Use with IETF
 *     Standards"
 *
 *    URL: https://tools.ietf.org/html/rfc5114
 *
 *  Copyright(c) 2021 Mitya Selivanov
 *
 *  This file is part of the Laplace project.
 *
 *  Laplace is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 *  the MIT License for more details.
 */

#ifndef laplace_network_crypto_prime_h
#define laplace_network_crypto_prime_h

#include <cstdint>

namespace laplace::network::crypto {
  /*  2048-bit MODP Group with 256-bit Prime Order Subgroup
   */

  constexpr uint8_t prime[] = {
    0xac, 0x40, 0x32, 0xef, 0x4f, 0x2d, 0x9a, 0xe3, 0x9d, 0xf3, 0x0b,
    0x5c, 0x8f, 0xfd, 0xac, 0x50, 0x6c, 0xde, 0xbe, 0x7b, 0x89, 0x99,
    0x8c, 0xaf, 0x74, 0x86, 0x6a, 0x08, 0xcf, 0xe4, 0xff, 0xe3, 0xa6,
    0x82, 0x4a, 0x4e, 0x10, 0xb9, 0xa6, 0xf0, 0xdd, 0x92, 0x1f, 0x01,
    0xa7, 0x0c, 0x4a, 0xfa, 0xab, 0x73, 0x9d, 0x77, 0x00, 0xc2, 0x9f,
    0x52, 0xc5, 0x7d, 0xb1, 0x7c, 0x62, 0x0a, 0x86, 0x52, 0xbe, 0x5e,
    0x90, 0x01, 0xa8, 0xd6, 0x6a, 0xd7, 0xc1, 0x76, 0x69, 0x10, 0x19,
    0x99, 0x02, 0x4a, 0xf4, 0xd0, 0x27, 0x27, 0x5a, 0xc1, 0x34, 0x8b,
    0xb8, 0xa7, 0x62, 0xd0, 0x52, 0x1b, 0xc9, 0x8a, 0xe2, 0x47, 0x15,
    0x04, 0x22, 0xea, 0x1e, 0xd4, 0x09, 0x93, 0x9d, 0x54, 0xda, 0x74,
    0x60, 0xcd, 0xb5, 0xf6, 0xc6, 0xb2, 0x50, 0x71, 0x7c, 0xbe, 0xf1,
    0x80, 0xeb, 0x34, 0x11, 0x8e, 0x98, 0xd1, 0x19, 0x52, 0x9a, 0x45,
    0xd6, 0xf8, 0x34, 0x56, 0x6e, 0x30, 0x25, 0xe3, 0x16, 0xa3, 0x30,
    0xef, 0xbb, 0x77, 0xa8, 0x6f, 0x0c, 0x1a, 0xb1, 0x5b, 0x05, 0x1a,
    0xe3, 0xd4, 0x28, 0xc8, 0xf8, 0xac, 0xb7, 0x0a, 0x81, 0x37, 0x15,
    0x0b, 0x8e, 0xeb, 0x10, 0xe1, 0x83, 0xed, 0xd1, 0x99, 0x63, 0xdd,
    0xd9, 0xe2, 0x63, 0xe4, 0x77, 0x05, 0x89, 0xef, 0x6a, 0xa2, 0x1e,
    0x7f, 0x5f, 0x2f, 0xf3, 0x81, 0xb5, 0x39, 0xcc, 0xe3, 0x40, 0x9d,
    0x13, 0xcd, 0x56, 0x6a, 0xfb, 0xb4, 0x8d, 0x6c, 0x01, 0x91, 0x81,
    0xe1, 0xbc, 0xfe, 0x94, 0xb3, 0x02, 0x69, 0xed, 0xfe, 0x72, 0xfe,
    0x9b, 0x6a, 0xa4, 0xbd, 0x7b, 0x5a, 0x0f, 0x1c, 0x71, 0xcf, 0xff,
    0x4c, 0x19, 0xc4, 0x18, 0xe1, 0xf6, 0xec, 0x01, 0x79, 0x81, 0xbc,
    0x08, 0x7f, 0x2a, 0x70, 0x65, 0xb3, 0x84, 0xb8, 0x90, 0xd3, 0x19,
    0x1f, 0x2b, 0xfa
  };

  constexpr uint8_t generator[] = {
    0x3f, 0xb3, 0x2c, 0x9b, 0x73, 0x13, 0x4d, 0x0b, 0x2e, 0x77, 0x50,
    0x66, 0x60, 0xed, 0xbd, 0x48, 0x4c, 0xa7, 0xb1, 0x8f, 0x21, 0xef,
    0x20, 0x54, 0x07, 0xf4, 0x79, 0x3a, 0x1a, 0x0b, 0xa1, 0x25, 0x10,
    0xdb, 0xc1, 0x50, 0x77, 0xbe, 0x46, 0x3f, 0xff, 0x4f, 0xed, 0x4a,
    0xac, 0x0b, 0xb5, 0x55, 0xbe, 0x3a, 0x6c, 0x1b, 0x0c, 0x6b, 0x47,
    0xb1, 0xbc, 0x37, 0x73, 0xbf, 0x7e, 0x8c, 0x6f, 0x62, 0x90, 0x12,
    0x28, 0xf8, 0xc2, 0x8c, 0xbb, 0x18, 0xa5, 0x5a, 0xe3, 0x13, 0x41,
    0x00, 0x0a, 0x65, 0x01, 0x96, 0xf9, 0x31, 0xc7, 0x7a, 0x57, 0xf2,
    0xdd, 0xf4, 0x63, 0xe5, 0xe9, 0xec, 0x14, 0x4b, 0x77, 0x7d, 0xe6,
    0x2a, 0xaa, 0xb8, 0xa8, 0x62, 0x8a, 0xc3, 0x76, 0xd2, 0x82, 0xd6,
    0xed, 0x38, 0x64, 0xe6, 0x79, 0x82, 0x42, 0x8e, 0xbc, 0x83, 0x1d,
    0x14, 0x34, 0x8f, 0x6f, 0x2f, 0x91, 0x93, 0xb5, 0x04, 0x5a, 0xf2,
    0x76, 0x71, 0x64, 0xe1, 0xdf, 0xc9, 0x67, 0xc1, 0xfb, 0x3f, 0x2e,
    0x55, 0xa4, 0xbd, 0x1b, 0xff, 0xe8, 0x3b, 0x9c, 0x80, 0xd0, 0x52,
    0xb9, 0x85, 0xd1, 0x82, 0xea, 0x0a, 0xdb, 0x2a, 0x3b, 0x73, 0x13,
    0xd3, 0xfe, 0x14, 0xc8, 0x48, 0x4b, 0x1e, 0x05, 0x25, 0x88, 0xb9,
    0xb7, 0xd2, 0xbb, 0xd2, 0xdf, 0x01, 0x61, 0x99, 0xec, 0xd0, 0x6e,
    0x15, 0x57, 0xcd, 0x09, 0x15, 0xb3, 0x35, 0x3b, 0xbb, 0x64, 0xe0,
    0xec, 0x37, 0x7f, 0xd0, 0x28, 0x37, 0x0d, 0xf9, 0x2b, 0x52, 0xc7,
    0x89, 0x14, 0x28, 0xcd, 0xc6, 0x7e, 0xb6, 0x18, 0x4b, 0x52, 0x3d,
    0x1d, 0xb2, 0x46, 0xc3, 0x2f, 0x63, 0x07, 0x84, 0x90, 0xf0, 0x0e,
    0xf8, 0xd6, 0x47, 0xd1, 0x48, 0xd4, 0x79, 0x54, 0x51, 0x5e, 0x23,
    0x27, 0xcf, 0xef, 0x98, 0xc5, 0x82, 0x66, 0x4b, 0x4c, 0x0f, 0x6c,
    0xc4, 0x16, 0x59
  };
}

#endif
