#pragma once
#include <fmt/format.h>   
#include "point.hpp"

namespace fmt {

 template <typename T, typename Char>
 struct formatter<Point<T>, Char> : formatter<std::basic_string_view<Char>, Char> {
  template <typename FormatContext>
  auto format(const Point<T>& p, FormatContext& ctx) const {
    return fmt::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
 };

}