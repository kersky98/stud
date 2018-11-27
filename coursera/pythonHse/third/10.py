# Даны действительные коэффициенты a, b, c, при этом a != 0. Решите
# квадратное уравнение ax²+bx+c=0 и выведите все его корни.

import math

a = float(input())
b = float(input())
c = float(input())

d = b**2 - 4*a*c

if d > 0:
    x1 = (-b - math.sqrt(d)) / (2*a)
    x2 = (-b + math.sqrt(d)) / (2*a)
    if x1 > x2:
        print(x2, x1)
    else:
        print(x1, x2)
elif d == 0:
    x = -b / (2*a)
    print(x)
