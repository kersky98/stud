# Проверьте, принадлежит ли точка данной закрашенной области:


# Если точка принадлежит области (область включает границы), выведите слово
# YES, иначе выведите слово NO. Решение должно содержать функцию
# IsPointInArea(x, y), возвращающую True, если точка принадлежит области и
# False, если не принадлежит. Основная программа должна считать координаты
# точки, вызвать функцию IsPointInArea и в зависимости от возвращенного
# значения вывести на экран необходимое сообщение. Функция IsPointInArea не
# должна содержать инструкцию if.

import sys
from math import sqrt

x = float(input())
y = float(input())

e = sys.float_info.epsilon
# уравнения прямых:
# x + y = 0
# x - 0.5*y + 1 = 0
# x + y <= 0+e -точки слева от прямой


def IsPointInArea(x, y):
    r = 2.0
    rn = sqrt((x+1)**2 + (y-1)**2)
    res = x + y <= 0+e and x - 1/2*y + 1 >= 0-e and rn >= r-e or \
        x + y >= 0-e and x - 1/2*y + 1 <= 0+e and rn <= r+e
    return res


if IsPointInArea(x, y):
    print('YES')
else:
    print('NO')
