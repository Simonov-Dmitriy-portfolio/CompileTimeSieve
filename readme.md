Решето позволяет при поиске простых чисел отфильтровать
числа, которые заведомо не являются простыми, а именно те,
которые являются кратными первым простым числам (назовём эти простые числа базовыми).
В тривиальном случае все чётные числа не являются простыми.

В отличие от решета Эратосфена это решето не даёт готового множества простых чисел
(в тривиальном случае не все нечётные числа являются простыми).

Но опять же в отличие от решета Эратосфена, это решето можно применять на всём диапазоне целых чисел,
притом что определяется оно на сравнительно коротком диапазоне (от 1 до примориала выбранного максимального простого числа).
Распространение выполняется путём сдвига чисел, оставшихся в решете, на целое число примориалов.

Например, рассмотрим числа, кратные 2 и 3. Их примориал 2 * 3 = 6. В диапазоне от 1 до 6 отфильтровываются числа 2, 3, 4, 6. Остаются числа 1 и 5.
Если прибавить к числам этого фильтра примориал (6), то получим, что в диапазоне от 7 до 12 отфильтровываются числа 8, 9, 10, 12 и остаются 7, 11.
Аналогично в диапазоне от 13 до 18 отфильтровываем 14, 15, 16, 18 и оставляем 13, 17. И так далее.
В диапазоне 24, 30 среди оставшихся после фильтрации появляется первое непростое число 25.

При расширении примориала числом 5 (2 * 3 * 5 = 30) дополнительно отбрасываются числа 5, 25, за счёт чего доля отфильтрованных чисел увеличивается.

Увеличение доли отфильтрованных чисел замедляется с каждым новым базовым простым числом.
При этом количество чисел, оставшихся в решете, увеличивается экспоненциально и даже быстрее. Это ограничивает эффективность фильтра.
Для примориала 19 при расходе памяти примерно 6,5М удаётся исключить примерно 83% чисел.

Здесь ради эксперимента решето строится во время компиляции.
