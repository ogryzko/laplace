/*  laplace/engine/basic_factory.h
 *
 *      Prime impact factory.
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

#ifndef laplace_engine_basic_factory_h
#define laplace_engine_basic_factory_h

#include "prime_impact.h"

namespace laplace::engine {
  /*  Prime impact factory performs deserialization.
   */
  class basic_factory {
  public:
    using fn_name_by_id = std::function<std::string(uint16_t)>;
    using fn_id_by_name = std::function<uint16_t(std::string_view)>;

    basic_factory()          = default;
    virtual ~basic_factory() = default;

    virtual auto parse(std::string_view command) const -> vbyte;
    virtual auto print(span_cbyte seq) const -> std::string;

    virtual auto decode(span_cbyte seq) const -> ptr_prime_impact;

    auto parse_multi(std::string_view commands) const
        -> sl::vector<vbyte>;
    auto print_multi(std::span<const span_cbyte> seqs) const
        -> std::string;

    static auto id_by_name_native(std::string_view name) -> uint16_t;
    static auto name_by_id_native(uint16_t id) -> std::string;

    static auto parse_native(fn_id_by_name    id_by_name,
                             std::string_view command) -> vbyte;

    static auto print_native(fn_name_by_id name_by_id, span_cbyte seq)
        -> std::string;

    static auto decode_native(span_cbyte seq) -> ptr_prime_impact;

    template <typename impact_type_>
    static auto make(span_cbyte seq) -> ptr_prime_impact;
  };

  using ptr_factory = std::shared_ptr<basic_factory>;
}

#include "basic_factory.impl.h"

#endif
