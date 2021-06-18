#pragma once

#include <bit>
#include <functional>

#include "random/detail/select_uint_least_t.hpp"

namespace reki::detail
{
  template <typename T, T m, T a, T c,
            bool BigEnough = (!(m & (m - 1)) ||
                              std::greater_equal{}((static_cast<T>(-1) - c) / a,
                                                   m - 1)),
            bool SchrageOk = std::less{}(m % a, m / a)>
  struct mod_impl final
  {
    using type = select_uint_least_t<std::bit_width(a) + std::bit_width(m)>;

    static constexpr T calc(T x) noexcept
    {
      return static_cast<T>((type{a} * x + c) % m);
    }
  };

  template <typename T, T m, T a, T c>
  struct mod_impl<T, m, a, c, false, true> final
  {
    static constexpr T calc(T x);
  };

  template <typename T, T m, T a, T c, bool s>
  struct mod_impl<T, m, a, c, true, s> final
  {
    static constexpr T calc(T x)
    {
      T res = a * x + c;

      return m ? res % m : res;
    }
  };

  template <std::unsigned_integral T, T m, T a = 1, T c = 0>
  inline constexpr T mod(T x)
  {
    if constexpr (a == 0)
    {
      return c;
    }
    else
    {
      return mod_impl<T, m, std::max(a, T{1}), c>::calc(x);
    }
  }
}
