# Дана последовательность чисел, завершающаяся числом 0.
# Найдите сумму всех этих чисел, не используяцикл.


def summ():
    n = int(input())
    if n == 0:
        return 0
    else:
        return n+summ()


# n = int(input())
print(summ())
