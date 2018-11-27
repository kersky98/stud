# Напишите функцию, вычисляющую длину отрезка по координатам его концов.
# С помощью этой функции напишите программу, вычисляющую периметр треугольника
# по координатам трех его вершин.

x1 = int(input())
y1 = int(input())
x2 = int(input())
y2 = int(input())
x3 = int(input())
y3 = int(input())


def distance(x1, y1, x2, y2):
    d = ((x2-x1)**2 + (y2-y1)**2)**0.5
    return d


def perimeter(x1, y1, x2, y2, x3, y3):
    p = distance(x1, y1, x2, y2) + distance(x1, y1, x3, y3) +\
        distance(x2, y2, x3, y3)
    return p


print(perimeter(x1, y1, x2, y2, x3, y3))
