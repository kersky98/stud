# Переставьте соседние элементы списка (A[0] c A[1],A[2] c A[3] и т.д.).
# Если элементов нечетное число, то последний элемент остается на своем месте.

# n = int(input())
m = list(map(int, input().split()))
# k = int(input())

# m = [4, 5, 3, 4, 2]

for index, item in enumerate(m):
    if index % 2 != 0:
        # print(item)
        tmp = m[index-1]
        m[index-1] = m[index]
        m[index] = tmp

print(*m)
