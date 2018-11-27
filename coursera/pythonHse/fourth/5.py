# Даны два действительных числа x и y. Проверьте, принадлежит ли точка с
# координатами(x,y) заштрихованному квадрату (включая его границу). Если точка
# принадлежит квадрату, выведите слово YES,иначе выведите слово NO.
# На рисунке сетка проведена с шагом 1.
# Решение должно содержать функцию IsPointInSquare(x, y), возвращающую True,
# если точка принадлежит квадрату и False, если не принадлежит. Основная
# программа должна считать координаты точки, вызвать функцию IsPointInSquareи в
# зависимости от возвращенного значения вывести на экран необходимое сообщение.
# Функция IsPointInSquare не должна содержать инструкцию if.

import sys
from math import sqrt

x1 = float(input())
y1 = float(input())

e = sys.float_info.epsilon
k = sqrt(2.0)/2.0

x = k*x1 + k*y1
y = -k*x1 + k*y1


def IsPointInSquare(x, y):
    res = -k-e < x < k+e and -k-e < y < k+e
    return res


if IsPointInSquare(x, y):
    print('YES')
else:
    print('NO')
