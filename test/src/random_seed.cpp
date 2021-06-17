#include "random/random_seed.hpp"

#include <boost/ut.hpp>

int main()
{
  auto seed1 = reki::random_seed{}();

  auto seed2 = reki::random_seed{}();

  boost::ut::expect(boost::ut::neq(seed1, seed2));
}
