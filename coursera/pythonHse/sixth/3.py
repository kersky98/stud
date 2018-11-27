# Отсортируйте данный массив, используя встроенную сортировку.

n = int(input())
m = list(map(int, input().split()))
m.sort()
print(*m)
