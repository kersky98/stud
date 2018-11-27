x1 = int(input())
y1 = int(input())
x2 = int(input())
y2 = int(input())

dx = x2 - x1
dy = y2 - y1

if dx < 0:
    dx = -dx
if dy < 0:
    dy = -dy

if dx <= 1 and dy <= 1:
    print('YES')
else:
    print('NO')
