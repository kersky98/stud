# Даны вещественные числа a, b, c, d, e, f. Известно, что система линейных
# уравнений:
# ax + by = e
# cx + dy = f
# имеет ровно одно решение. Выведите два числа x и y, являющиеся решением
# этой системы.

a = float(input())
b = float(input())
c = float(input())
d = float(input())
e = float(input())
f = float(input())

# a = 1
# b = 2
# c = 3
# d = 4
# e = -1
# f = -1

opr = a*d - b*c
oprx = e*d - b*f
opry = a*f - e*c

x = oprx / opr
y = opry / opr

print(x, y)
