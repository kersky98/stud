# Процентная ставка по вкладу составляет P процентов годовых, которые
# прибавляются к сумме вклада через год. Вклад составляет X рублей Y копеек.
# Определите размер вклада через K лет.

# import math

p = int(input())
x = int(input())
y = int(input())
k = int(input())

v = 100*x + y
vp = int((v * p) / 100)
# v = v1 + v2

i = 0
while i < k:
    v += int((v * p) / 100)
    i += 1

rub = int(v/100)
kop = v % 100

print(rub, kop)
