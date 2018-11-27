x = int(input())
y = int(input())

n = y - x + 1

if n < x and x != 1 and y % n == 0 or x == 1:
    print('YES')
else:
    print('NO')
