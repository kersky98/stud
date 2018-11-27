# Дано действительное положительное число a и целоe число n. Вычислите aⁿ.
# Решение оформите в виде функции power(a, n). Стандартной функцией возведения
# в степень пользоваться нельзя.

a = float(input())
n = int(input())


def power(a, n):
    res = a
    if n > 1:
        res *= power(a, n-1)
    elif n == 0:
        res = 1
    return res


res = power(a, abs(n))
if n >= 0:
    print(res)
else:
    print(1.0/res)
