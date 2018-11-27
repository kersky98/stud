# Есть две коробки, первая размером A₁×B₁×C₁, вторая размером A₂×B₂×C₂.\
# Определите, можно ли разместить одну из этих коробок внутри другой, \
# при условии, что поворачивать коробки можно только на 90 градусов\
# вокруг ребер.

a1 = int(input())
b1 = int(input())
c1 = int(input())
a2 = int(input())
b2 = int(input())
c2 = int(input())

# проверка на существование
isExist = a1 > 0 and b1 > 0 and c1 > 0 and\
 a2 > 0 and b2 > 0 and c2 > 0

isEqual = isExist and \
 a1 == a2 and b1 == b2 and c1 == c2 or\
 a1 == a2 and b1 == c2 and c1 == b2 or\
 a1 == b2 and b1 == a2 and c1 == c2 or\
 a1 == b2 and b1 == c2 and c1 == a2 or\
 a1 == c2 and b1 == a2 and c1 == b2 or\
 a1 == c2 and b1 == b2 and c1 == a2

isFirstSmallerSecond = isExist and \
 a2 >= a1 and b2 >= b1 and c2 >= c1 or\
 a2 >= a1 and b2 >= c1 and c2 >= b1 or\
 a2 >= b1 and b2 >= a1 and c2 >= c1 or\
 a2 >= b1 and b2 >= c1 and c2 >= a1 or\
 a2 >= c1 and b2 >= b1 and c2 >= a1 or\
 a2 >= c1 and b2 >= a1 and c2 >= b1

isFirstLargerSecond = isExist and \
 a1 >= a2 and b1 >= b2 and c1 >= c2 or\
 a1 >= a2 and b1 >= c2 and c1 >= b2 or\
 a1 >= b2 and b1 >= a2 and c1 >= c2 or\
 a1 >= b2 and b1 >= c2 and c1 >= a2 or\
 a1 >= c2 and b1 >= b2 and c1 >= a2 or\
 a1 >= c2 and b1 >= a2 and c1 >= b2

if isEqual:
    print('Boxes are equal')
elif isFirstSmallerSecond:
    print('The first box is smaller than the second one')
elif isFirstLargerSecond:
    print('The first box is larger than the second one')
else:
    print('Boxes are incomparable')
