# Дан список чисел. Если в нем есть два соседних элемента одного знака,
# выведите эти числа. Если соседних элементов одного знака нет - не выводите
# ничего. Если таких пар соседей несколько - выведите первую пару.

s = list(map(int, input().split()))

p = list()


def sign(a):
    if a > 0:
        return 1
    elif a < 0:
        return -1
    else:
        return 0


for index, item in enumerate(s):
    if index > 0:
        if sign(s[index]) == sign(s[index-1]):
            p.append(s[index-1])
            p.append(s[index])
            break

if len(p) > 0:
    print(p[0], p[1])
