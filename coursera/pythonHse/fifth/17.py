# Дан список чисел. Выведите значение наибольшего элемента в списке, а затем
# индекс этого элемента в списке. Если наибольших элементов несколько, выведите
# индекс первого из них.

s = list(map(int, input().split()))
nmax = max(s)
ind = 0
for index, item in enumerate(s):
    if item == nmax:
        ind = index
        break

print(nmax, ind)
