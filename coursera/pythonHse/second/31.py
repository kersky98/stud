# Определите сумму всех элементов последовательности, завершающейся числом 0.

n = int(input())
cnt = n
while n != 0:
    n = int(input())
    cnt += n

print(cnt)
