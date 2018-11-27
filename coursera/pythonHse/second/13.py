# Даны три стороны треугольника a,b,c. Определите тип треугольника \
# с заданными сторонами. Выведите одно из четырех слов: rectangular \
# для прямоугольного треугольника, acute для остроугольного треугольника,\
# obtuse для тупоугольного треугольника или impossible, если треугольника с \
# такими сторонами не существует.

a = int(input())
b = int(input())
c = int(input())

# сортировака сторон по возрастанию (не убыванию)
if (a > b):
    (a, b) = (b, a)

if (b > c):
    (b, c) = (c, b)

if (a > b):
    (a, b) = (b, a)

if (b > c):
    (b, c) = (c, b)

# найдем гипотенузу
# c - гипотенуза, а и b катеты

isRectangular = c**2 == a**2 + b**2
isAcute = c**2 < a**2 + b**2
isObtuse = c**2 > a**2 + b**2
isImpossible = c >= a + b or a >= b + c or b >= a + c or\
  a <= 0 or b <= 0 or c <= 0

if isImpossible:
    print('impossible')
else:
    if isRectangular:
        print('rectangular')
    elif isAcute:
        print('acute')
    elif isObtuse:
        print('obtuse')
    else:
        print('isImpossible1')
