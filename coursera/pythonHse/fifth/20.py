# Выведите элементы данного списка в обратном порядке, не изменяя сам список.

s = list(map(int, input().split()))

for item in s[::-1]:
    print(item, end=' ')
