#include "random/random_seed.hpp"

#include <array>
#include <boost/ut.hpp>

int main()
{
  using namespace boost::ut;

  "Different values if generated on different positon"_test =
    []()
    {
      constexpr auto seed1 = reki::random_seed{}();

      constexpr auto seed2 = reki::random_seed{}();

      expect(neq(seed1, seed2));
    };

  "Same values if generated on same position"_test =
    []()
    {
      std::array<reki::random_seed::result_type, 2> seeds{};

      std::ranges::generate(seeds, reki::random_seed{});

      expect(eq(seeds[0], seeds[1]));
    };
}
