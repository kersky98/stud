# Дана последовательность натуральных чисел x₁ x₂ ..., xn.
# Стандартным отклонением называется величина
# σ=sqrt(((((x₁-s)²+(x₂-s)²+…+(xn-s)²) / (n-1))))
# где s = ((x₁+x₂+…+xn) / n) — среднее арифметическое последовательности,
# а sqrt - квадартный корень. Определите стандартное отклонение для данной
# последовательности натуральных чисел,завершающейся числом 0.

import math

n = int(input())
s = 0
nstr = ''
cnt = 0

while n != 0:
    s += n
    nstr += str(n) + '/'
    cnt += 1
    n = int(input())
nstr += '0'
s /= cnt
# print(nstr)
# print(s)

nchar = ''
nstrsub = ''
nsub = 0
sigma = 0
scnt = 0
while not(nchar == '0' and nstrsub == ''):
    if nchar != '/':
        nstrsub += nchar
    else:
        # print(nstrsub)
        nsub = int(nstrsub)
        nstrsub = ''
        sigma += (nsub - s)**2
    nchar = nstr[scnt]
    scnt += 1

sigma /= cnt - 1
sigma = math.sqrt(sigma)
print(sigma)
