#pragma once

#include <concepts>
#include <cstddef>
#include <limits>

namespace reki::detail
{
  template <std::unsigned_integral UIntType, std::size_t w>
  inline constexpr UIntType shift
  = (w < static_cast<std::size_t>(std::numeric_limits<UIntType>::digits))
    ? (UIntType{1} << w) : 0;
}
