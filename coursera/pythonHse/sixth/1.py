# Даны два целочисленных списка A и B, упорядоченных по неубыванию.
# Объедините их в один упорядоченный список С (то есть он должен содержать
# len(A)+len(B) элементов). Решение оформите в виде функции merge(A, B),
# возвращающей новый список. Алгоритм должен иметь сложность O(len(A)+len(B)).
# Модифицировать исходные списки запрещается. Использовать функцию sorted и
# метод sort запрещается.

a = list(map(int, input().split()))
b = list(map(int, input().split()))
# a = [1, 5, 7]
# b = [2, 4, 4, 5]
# a = [1, 4, 7]
# b = [1, 5, 6]
# a = [1]
# b = [1]


def merge1(a, b):
    c = a + b
    c.sort()
    return c


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


print(*merge(a, b))
