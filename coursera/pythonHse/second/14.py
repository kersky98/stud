# Даны три целых числа A, B, C. Определить, есть ли среди них хотя \
# бы одно четное и хотя бы одно нечетное.

a = int(input())
b = int(input())
c = int(input())

isEven = a % 2 == 0 or b % 2 == 0 or c % 2 == 0
isNotEven = a % 2 == 1 or b % 2 == 1 or c % 2 == 1

if isEven and isNotEven:
    print('YES')
else:
    print('NO')
