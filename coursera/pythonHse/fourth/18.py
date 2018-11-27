# По данным числам n и k (0≤k≤n) вычислите C из n по k.
# Решение оформите в виде функции C(n, k).
# Для решения используйте рекуррентное соотношение:
# c(n, k) = c(n-1, k) + c(n-1, k-1)
# И равенства:
# С(n, 1)=n
# C(n, n)=1


n = int(input())
k = int(input())


def cnk(n, k):
    if k == 0 or n == 0:
        return 1
    if k == 1:
        return n
    if n == k:
        return 1
    res = cnk(n-1, k) + cnk(n-1, k-1)
    return res


print(cnk(n, k))
