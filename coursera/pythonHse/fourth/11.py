# Дано действительное положительное число a и целое неотрицательное число n.
# Вычислите aⁿ, не используя циклы и стандартную функцию pow, но используя
# рекуррентное соотношение aⁿ=a⋅aⁿ⁻¹.

a = float(input())
n = int(input())


def power(a, n):
    res = a
    if n > 1:
        res *= power(a, n-1)
    elif n == 0:
        res = 1
    return res


print(power(a, n))
