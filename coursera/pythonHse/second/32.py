# Определите среднее значение всех элементов последовательности, завершающейся
# числом 0. Использовать массивы в данной задаче нельзя.

n = int(input())
cnt = 0
summ = n
while n != 0:
    n = int(input())
    cnt += 1
    summ += n

print(summ / cnt)
