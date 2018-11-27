# Циклически сдвиньте элементы списка вправо(A[0] переходит на место A[1], A[1]
# на место A[2], ..., последний элемент переходит на место A[0]).
# Примечания
# Используйте минимально возможное количество операций присваивания.
# Не используйте срезы.
# Измените начальный список и вывдите ответ с помощью print(*listName).

# n = int(input())
m = list(map(int, input().split()))
# k = int(input())

# m = [1, 2, 3, 4, 5]
sz = len(m)
# prev = m[0]
# for index, item in enumerate(m):
#     if index+1 < sz:
#         tmp = m[index+1]
#         m[index+1] = prev
#         prev = tmp
# m[0] = tmp
tmp = m[sz-1]
for i in range(sz-1, 0, -1):
    # print(i)
    m[i] = m[i-1]
m[0] = tmp
print(*m)
