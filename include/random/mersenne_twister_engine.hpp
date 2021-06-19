#pragma once

#include <array>
#include <concepts>
#include <limits>

#include "random/detail/mod.hpp"
#include "random/detail/select_uint_least_t.hpp"
#include "random/detail/shift.hpp"

namespace reki
{
  template <std::unsigned_integral UIntType,
            std::size_t w, std::size_t n, std::size_t m, std::size_t r,
            UIntType a, std::size_t u, UIntType d, std::size_t s,
            UIntType b, std::size_t t,
            UIntType c, std::size_t l, UIntType f>
  requires (1u <= m && m <= n)   && (r <= w) && (u <= w)   &&
           (s <= w) && (t <= w)  && (l <= w) &&
           (w <= std::numeric_limits<UIntType>::digits)    &&
           (a <= (detail::shift<UIntType, w> - 1))         &&
           (b <= (detail::shift<UIntType, w> - 1))         &&
           (c <= (detail::shift<UIntType, w> - 1))         &&
           (d <= (detail::shift<UIntType, w> - 1))         &&
           (f <= (detail::shift<UIntType, w> - 1))
  class mersenne_twister_engine final
  {
  public:
    // Public Types
    using result_type = UIntType;

    // Static Pubic Members
    static constexpr std::size_t word_size                 = w;

    static constexpr std::size_t state_size                = n;

    static constexpr std::size_t shift_size                = m;

    static constexpr std::size_t mask_bits                 = r;

    static constexpr result_type xor_mask                  = a;

    static constexpr std::size_t tempering_u               = u;

    static constexpr result_type tempering_d               = d;

    static constexpr std::size_t tempering_s               = s;

    static constexpr result_type tempering_b               = b;

    static constexpr std::size_t tempering_t               = t;

    static constexpr result_type tempering_c               = c;

    static constexpr std::size_t tempering_l               = l;

    static constexpr result_type initialization_multiplier = f;

    static constexpr result_type default_seed              = 5489u;

    // Constructor
    constexpr mersenne_twister_engine(result_type value = default_seed)
    {
      seed(std::move(value));
    }

    // Static Public Methods
    static constexpr result_type min() noexcept
    {
      return 0;
    }

    static constexpr result_type max() noexcept
    {
      return detail::shift<result_type, w> - 1u;
    }

    // Public Methods
    constexpr void seed(result_type seed = default_seed)
    {
      state_sequence_.front()
      = detail::mod<result_type, detail::shift<result_type, w>>(seed);

      for (std::size_t i = 1; i < state_size; ++i)
      {
        result_type x = state_sequence_[i - 1];

        x ^= x >> (w - 2);

        x *= f;

        x += detail::mod<result_type, n>(i);

        state_sequence_[i]
        = detail::mod<result_type, detail::shift<result_type, w>>(x);
      }

      pos_ = state_size;
    }

    constexpr void discard(unsigned long long z)
    {
      while (z > state_size - pos_)
      {
        z -= state_size - pos_;

        gen_rand_();
      }

      pos_ += z;
    }

    constexpr result_type operator()()
    {
      if (pos_ >= state_size)
      {
        gen_rand_();
      }

      result_type z = state_sequence_[pos_++];

      z ^= (z >> u) & d;

      z ^= (z << s) & b;

      z ^= (z << t) & c;

      z ^= (z >> l);

      return z;
    }

  private:
    // Private Members
    std::array<result_type, state_size> state_sequence_{};

    std::size_t                         pos_{};

    // Private Methods
    constexpr void gen_rand_()
    {
      constexpr result_type upper_mask = (~result_type{}) << r;

      constexpr result_type lower_mask = ~upper_mask;

      for (std::size_t k = 0, end = n - m; k < end; ++k)
      {
        result_type y = ((state_sequence_[k] & upper_mask)
                         | (state_sequence_[k + 1] & lower_mask));

        state_sequence_[k] = (state_sequence_[k + m] ^ (y >> 1)
                              ^ ((y & 0x01) ? a : 0));
      }

      for (std::size_t k = (n - m), end = n - 1; k < end; ++k)
      {
        result_type y = ((state_sequence_[k] & upper_mask)
                         | (state_sequence_[k + 1] & lower_mask));

        state_sequence_[k] = (state_sequence_[k + (m - n)]
                              ^ (y >> 1) ^ ((y & 0x01) ? a : 0));
      }

      result_type y = ((state_sequence_[n - 1]  & upper_mask) |
                       (state_sequence_.front() & lower_mask));

      state_sequence_[n - 1] = (state_sequence_[m - 1] ^ (y >> 1)
                                ^ ((y & 0x01) ? a : 0));

      pos_ = 0;
    }
  };
}
