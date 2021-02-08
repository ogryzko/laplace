#ifndef __laplace__ui_elem_textedit__
#define __laplace__ui_elem_textedit__

#include "panel.h"

namespace laplace::ui::elem {
  class textedit final : public panel {
  public:
    using filter = std::function<bool(char32_t c)>;

    struct state : panel::state {
      bool          has_focus;
      std::u8string text;
      size_t        length_limit;
      size_t        cursor;
      int           selection;
    };

    struct update_result {
      bool          event_status;
      bool          has_focus;
      std::u8string text;
      size_t        cursor;
      int           selection;
    };

    static constexpr size_t default_length_limit = 24;

    ~textedit() final = default;

    void setup_filter(filter f);

    auto tick(size_t delta_msec, platform::ref_input in)
        -> bool final;
    void render() final;

    void set_text(std::u8string_view text);
    void set_length_limit(size_t limit);
    void set_cursor(size_t cursor);
    void set_selection(int selection);

    auto get_text() const -> std::u8string_view;
    auto get_cursor() const -> size_t;
    auto get_selection() const -> int;

    auto get_state() const -> state;

    static auto update(ptr_widget object, state textedit_state,
                       filter f, platform::ref_input in)
        -> update_result;

  private:
    auto textedit_tick(platform::ref_input in) -> bool;

    filter        m_filter;
    size_t        m_length_limit = default_length_limit;
    std::u8string m_text;
    size_t        m_cursor    = 0;
    int           m_selection = 0;
  };

  using ptr_textedit = std::shared_ptr<textedit>;
}

#endif
