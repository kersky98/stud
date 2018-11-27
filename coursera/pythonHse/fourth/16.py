# Даны два натуральных числа n и m.
# Сократите дробь (n / m), то есть выведите два других числа p и q таких,
# что (n / m) = (p / q) и дробь (p / q) — несократимая.
# Решение оформите в виде функции ReduceFraction(n, m), получающая значения
# n и m и возвращающей кортеж из двух чисел (return p, q).

a = int(input())
b = int(input())
res = 0


def gcd(a, b):
    if b == 0:
        global res
        res = a
        return 0
    else:
        gcd(b, a % b)


def ReduceFraction(a, b):
    gcd(a, b)
    return a//res, b//res


a, b = ReduceFraction(a, b)
print(a, b)
