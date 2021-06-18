#pragma once

#include <cstdint>

#include "random/mersenne_twister_engine.hpp"

namespace reki
{
  using mt19937_64
  = mersenne_twister_engine<
      std::uint_fast64_t, 64, 312, 156, 31,
      0xb5026f5aa96619e9ULL, 29,
      0x5555555555555555ULL, 17,
      0x71d67fffeda60000ULL, 37,
      0xfff7eee000000000ULL, 43, 6364136223846793005ULL>;
}
