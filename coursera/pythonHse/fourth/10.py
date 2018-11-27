# Дано натуральное число n>1. Проверьте, является ли оно простым. Программа
# должна вывести слово YES, если число простое и NO, если число составное.
# Решение оформите в виде функции IsPrime(n), которая возвращает True для
# простых чисел и False для составных чисел. Программа должна иметь сложность
# O(корень из n): количество действий в программе должно быть пропорционально
# квадратному корню из n (иначе говоря, при увеличении входного числа в k раз,
# время выполнения программы должно увеличиваться примерно в корень из k раз).
from math import sqrt


def MinDivisor(n):
    index = 1
    lim = sqrt(n)
    res = n
    while index <= lim:
        index += 1
        if n % index == 0:
            res = index
            break
    return res


def IsPrime(n):
    if MinDivisor(n) == n:
        res = True
    else:
        res = False
    return res


n = int(input())

if IsPrime(n):
    print('YES')
else:
    print('NO')
