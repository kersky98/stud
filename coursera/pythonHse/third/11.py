# Даны произвольные действительные коэффициенты a, b, c.
# Решите уравнение ax²+bx+c=0.

import math

a = float(input())
b = float(input())
c = float(input())

d = b**2 - 4*a*c

if a != 0:
    if d > 0:
        x1 = (-b - math.sqrt(d)) / (2*a)
        x2 = (-b + math.sqrt(d)) / (2*a)
        if x1 > x2:
            print(2, x2, x1)
        else:
            print(2, x1, x2)
    elif d == 0:
        x = -b / (2*a)
        print(1, x)
    elif d < 0:
        print(0)
else:
    if b == 0 and c == 0:
        print(3)
    else:
        print(0)
