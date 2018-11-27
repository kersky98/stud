# Дано положительное действительное число X. Выведите его дробную часть.

# import math

a = float(input())

rub = int(a)
kop = round(100*(a - rub))

print(rub, kop)
