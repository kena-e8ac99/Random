#pragma once

#include <limits>
#include <source_location>

#include "hash/hash.hpp"

namespace reki
{
  struct random_seed final
  {
    // Public Types
    using result_type = unsigned int;

    // Public Static Methods
    static constexpr result_type min() noexcept
    {
      return std::numeric_limits<result_type>::min();
    }

    static constexpr result_type max() noexcept
    {
      return std::numeric_limits<result_type>::max();
    }

    // Public Operators
    constexpr result_type operator()(std::source_location loc
                                       = std::source_location::current()) const
    {
      return hash{}(std::tuple{loc.line(), loc.column(), loc.file_name(),
                               loc.function_name(), __DATE__, __TIME__});
    }
  };
}
