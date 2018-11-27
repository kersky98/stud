# Найдите количество положительных элементов в данном списке.

s = list(map(int, input().split()))

cnt = 0
for i in s:
    if i > 0:
        cnt += 1
print(cnt)
