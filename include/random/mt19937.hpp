#pragma once

#include <cstdint>

#include "random/mersenne_twister_engine.hpp"

namespace reki
{
  using mt19937
  = mersenne_twister_engine<
      std::uint_fast32_t, 32, 624, 397, 31, 0x9908b0dfUL, 11, 0xffffffffUL, 7,
      0x9d2c5680UL, 15, 0xefc60000UL, 18, 1812433253UL>;
}
