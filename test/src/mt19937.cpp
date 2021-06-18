#include "random/mt19937.hpp"

#include <algorithm>
#include <random>

#include <boost/ut.hpp>

using seed_type = reki::mt19937::result_type;

constexpr std::size_t test_size = 10000;

constexpr auto my_random_array()
{
  std::array<seed_type, test_size> result{};

  std::ranges::generate(result, reki::mt19937{});

  return result;
}

auto std_random_array()
{
  std::array<seed_type, test_size> result{};

  std::ranges::generate(result, std::mt19937{});

  return result;
}

int main()
{
  using namespace boost::ut;

  constexpr auto my_randoms = my_random_array();

  auto std_randoms = std_random_array();

  "reki::mt19937 == std::mt19937"_test =
    [&]()
    {
      bool is_equal = std::ranges::equal(my_randoms, std_randoms);

      expect(eq(is_equal, true));
    };

  "default constructed reki::mt19937[10000 - 1] == 4123659995"_test =
    [&]()
    {
      expect(eq(my_randoms[10000 - 1], seed_type{4123659995}));
    };
}
