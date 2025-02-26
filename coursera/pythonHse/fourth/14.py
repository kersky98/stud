# Возводить в степень можно гораздо быстрее, чем за n умножений! Для этого
# нужно воспользоваться следующими рекуррентными соотношениями: aⁿ = (a²)ⁿ/²
# при четном n, aⁿ=a⋅aⁿ⁻¹ при нечетном n. Реализуйте алгоритм быстрого
# возведения в степень. Если вы все сделаете правильно,то сложность вашего
# алгоритма будет O(logn).

a = float(input())
n = int(input())


def power(a, n):
    res = a
    if n > 1:
        if n % 2 != 0:
            res *= power(a, n-1)
        else:
            res = power(a*a, n/2)
    elif n == 0:
        res = 1
    return res


print(power(a, n))
