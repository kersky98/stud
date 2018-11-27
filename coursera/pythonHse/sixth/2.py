# Даны два списка, упорядоченных по возрастанию (каждый список состоит из
# различных элементов). Найдите пересечение множеств элементов этих списков,
# то есть те числа, которые являются элементами обоих списков. Алгоритм должен
# иметь сложность O(len(A)+len(B)). Решение оформите в виде функции
# Intersection(A, B). Функция должна возвращать список пересечения данных
# списков в порядке возрастания элементов. Модифицировать исходные списки
# запрещается.

a = list(map(int, input().split()))
b = list(map(int, input().split()))
# a = [1, 3, 4, 7, 9]
# b = [2, 3, 7, 10, 11]
# a = [1, 4, 6, 8]
# b = [1, 4, 6, 8]
# a = [2, 4, 6, 8, 10]
# b = [1, 3, 5, 7, 9]


def merge(a, b):
    lena = len(a)
    lenb = len(b)
    c = []

    if lena > lenb:
        len1 = lena
        len2 = lenb
        l1 = a
        l2 = b
    else:
        len1 = lenb
        len2 = lena
        l1 = b
        l2 = a

    index1 = 0
    index2 = 0
    for i in range(len1 + len2):
        if index1 < len1 and index2 < len2:
            if l1[index1] > l2[index2]:
                c.append(l2[index2])
                index2 += 1
            else:
                c.append(l1[index1])
                index1 += 1
        elif index1 < len1:
            while index1 < len1:
                c.append(l1[index1])
                index1 += 1
        elif index2 < len2:
            while index2 < len2:
                c.append(l2[index2])
                index2 += 1
    return c


def Intersection(a, b):
    c = merge(a, b)
    d = []
    for i in range(1, len(c)):
        if c[i-1] == c[i]:
            d.append(c[i])

    return d


print(*Intersection(a, b))
