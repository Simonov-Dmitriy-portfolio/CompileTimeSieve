//UTF-8
#ifndef SIEVE_H
#define SIEVE_H

#include <stdint.h>

using uint32 = uint32_t;
using uint64 = uint64_t;

//Решето позволяет при поиске простых чисел отфильтровать
//числа, которые заведомо не являются простыми, а именно те, которые являются кратными первым простым числам (назовём их базовыми).
//В тривиальном случае все чётные числа не являются простыми.
//В отличие от решета Эратосфена это решето не даёт готового множества простых чисел
//(в тривиальном случае не все нечётные числа являются простыми).
//Но опять же в отличие от решета Эратосфена, это решето можно применять на всём диапазоне целых чисел,
//притом что определяется оно на сравнительно коротком диапазоне (от 1 до примориала выбранного максимального простого числа).
//Распространение выполняется путём сдвига чисел, оставшихся в решете, на целое число примориалов.
//Например, рассмотрим числа, кратные 2 и 3. Их примориал 2 * 3 = 6. В диапазоне от 1 до 6 отфильтровываются числа 2, 3, 4, 6. Остаются числа 1 и 5.
//Если прибавить к числам этого фильтра примориал (6), то получим, что в диапазоне от 7 до 12 отфильтровываются числа 8, 9, 10, 12 и остаются 7, 11.
//Аналогично в диапазоне от 13 до 18 отфильтровываем 14, 15, 16, 18 и оставляем 13, 17. И так далее.
//В диапазоне 24, 30 среди оставшихся после фильтрации появляется первое непростое число 25.
//При расширении примориала числом 5 (2 * 3 * 5 = 30) дополнительно отбрасываются числа 5, 25, за счёт чего доля отфильтрованных чисел увеличивается.
//Увеличение доли отфильтрованных чисел замедляется с каждым новым базовым простым числом.
//При этом количество чисел, оставшихся в решете, увеличивается экспоненциально и даже быстрее. Это ограничивает эффективность фильтра.
//Для примориала 19 при расходе памяти примерно 6,5М удаётся исключить примерно 83% чисел.
//Здесь ради эксперимента решето строится во время компиляции.

static constexpr uint32 available_basic_primes[] = {2, 3, 5, 7, 11, 13, 17};

template<uint32 last_basic_prime>
class Sieve
{
public:
  constexpr Sieve() : m_sieve{1}
  {
    if (last_basic_prime == 2)
      return;

    m_sieve[1] = 5;
    uint32 primorial = 2 * 3;
    uint32 sieve_size = 2;

    uint32 tmp_sieve[sizeof(m_sieve)/sizeof(uint32)] = {};

    //Строим решето, наращивая в цикле базовые простые числа
    while (1)
    {
      //Первое число в фильтре всегда 1, второе является следующим базовым простым числом
      auto basic_prime = m_sieve[1];
      if (basic_prime > last_basic_prime)
        break;

      auto tmp_primorial = primorial;
      primorial *= basic_prime;

      uint32* tmp_end = tmp_sieve;

      size_t fi = 0;
      auto next_prime_factor = m_sieve[fi]; //первый сомножитель для нового базового простого числа (1)

      for (uint32 base = 0; base < primorial; base += tmp_primorial)
      {
        for (size_t i = 0; i < sieve_size; ++i)
        {
          auto sieve_num = base + m_sieve[i];
          if (fi < sieve_size && sieve_num == basic_prime * next_prime_factor)
          {
            //Отфильтровываем (не добавляем) кратное нового простого числа
            //Фиксируем следующий сомножитель нового простого числа
            next_prime_factor = m_sieve[++fi];
          }
          else
            *tmp_end++ = sieve_num;
        }
      }
      sieve_size *= (basic_prime - 1);
      for (size_t i = 0; i < sieve_size; ++i)
        m_sieve[i] = tmp_sieve[i];
    }
  }

  //Числа из решета, сдвинутые на целое число интервалов, сохраняют свои свойства
  //(не делятся на базовые простые). Все остальные делятся хотя бы на одно базовое простое
  static constexpr uint32 interval()
  {
    //Интервал определяется как примориал выбранного простого числа
    uint32 primorial = 1;
    //Здесь не может быть бесконечного цикла (см. функцию check_size)
    for (uint32 bpi = 0; ; ++bpi)
    {
      auto basic_prime = available_basic_primes[bpi];

      primorial *= basic_prime;

      if (basic_prime == last_basic_prime)
        break;
    }
    return primorial;
  }

  static constexpr uint32 size()
  {
    uint32 bp_count = sizeof(available_basic_primes) / sizeof(uint32);

    uint32 sieve_size = 1;
    uint32 bpi = 0;
    for (; bpi < bp_count; ++bpi)
    {
      auto basic_prime = available_basic_primes[bpi];

      sieve_size *= (basic_prime - 1);

      if (basic_prime == last_basic_prime)
        break;
    }
    return (bpi == bp_count) ? 0 : sieve_size;
  }

  constexpr uint32 operator[](uint32 i) const
  {
    return m_sieve[i];
  }

protected:
  static constexpr uint32 check_size()
  {
    constexpr auto s = size();
    static_assert(s > 0, "invalid last basic prime");
    return s;
  }

protected:
  uint32 m_sieve[check_size()];
};

#endif // SIEVE_H
