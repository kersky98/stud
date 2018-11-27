# Заданы две клетки шахматной доски. Если они покрашены в один цвет, \
# то выведите слово YES, а если в разные цвета – то NO.
x1 = int(input())
y1 = int(input())
x2 = int(input())
y2 = int(input())

# ищем манхэттенское расстояние
dx = x2 - x1
dy = y2 - y1

if dx < 0:
    dx = -dx
if dy < 0:
    dy = -dy
if (dx + dy) % 2 == 0:
    print('YES')
else:
    print('NO')


# if dx % 2 == 0 and dy % 2 == 0 or dx == dy:
#     print('YES')
# else:
#     print('NO')
