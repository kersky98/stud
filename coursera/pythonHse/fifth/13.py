# Дан список чисел. Выведите все элементы списка, которые больше предыдущего
# элемента.

s = list(map(int, input().split()))

for index, item in enumerate(s):
    if index > 0:
        if s[index] > s[index-1]:
            print(item, end=' ')
