# Напишите функцию phib(n), которая по данному целому неотрицательному n
# возвращает n-e число Фибоначчи. В этой задаче нельзя использовать циклы -
# используйте рекурсию.

n = int(input())
res = 1
resprev = 1
resprevprev = 0


def phib(n):
    global res, resprev, resprevprev
    if n > 1:
        res = resprev + resprevprev
        resprevprev = resprev
        resprev = res
        phib(n-1)
    return res


print(phib(n))
