//UTF-8

#include "compile_time_sieve/sieve.h"
#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

int main()
{
  constexpr uint32 last_basic_prime = 17;

  std::cout
    << "Sieve test" << std::endl
    << "last basic prime " << last_basic_prime << std::endl;

  constexpr Sieve<last_basic_prime> sieve;
  constexpr auto size = sieve.size();
  static_assert (size == 1 * 2 * 4 * 6 * 10 * 12 * 16, "invalid sieve size");
  static_assert (sieve[0] == 1, "invalid sieve[0]");
  static_assert (sieve[1] == 19, "invalid sieve[1]");

  constexpr auto interval = sieve.interval();
  static_assert (interval == 2 * 3 * 5 * 7 * 11 * 13 * 17, "invalid sieve interval");

  //Убедимся, что числа из решета, сдвинутые на произвольное количество интервалов, не делятся на базовые простые,
  //а остальные делятся на одно из них
  std::default_random_engine dre(time(0));
  std::uniform_int_distribution<uint32> dist;

  uint64 base = (uint64)(dist(dre)) * interval;

  uint32 sni = 0;
  auto sieve_num = base + sieve[sni];

  uint64 rem;

  for (auto num = base; num < base + interval; ++num)
  {
    for (uint32 bpi = 0; ; ++bpi)
    {
      auto basic_prime = available_basic_primes[bpi];
      rem = num % basic_prime;
      if (rem == 0 || basic_prime == last_basic_prime)
        break;
    }
    if (rem == 0) //Число поделилось на базовое простое, значит оно отфильтровано
      assert(num < sieve_num);
    else
    {
      assert(num == sieve_num);
      if (++sni < size)
      {
        //Числа в решете отсортированы по возрастанию
        assert(sieve[sni] > sieve[sni - 1]);
        sieve_num = base + sieve[sni];
      }
    }
  }

  assert(sni == size);

  std::cout
    << size << " / " << interval << " ~ " << size * 100 / interval << "% left in sieve" << std::endl
    << "ok" << std::endl;

  return 0;
}
