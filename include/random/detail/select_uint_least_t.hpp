#pragma once

#include <cstdint>
#include <functional>
#include <type_traits>

namespace reki::detail
{
  template <int N>
  requires (N <= 128)
  using select_uint_least_t
  = std::conditional_t<
      std::less_equal{}(N, sizeof(int)), unsigned int,
        std::conditional_t<std::less_equal{}(N, sizeof(long)), unsigned long,
          unsigned long long>>;
}
