# Определите наименьшее расстояние между двумя локальными максимумами
# последовательности натуральных чисел, завершающейся числом 0. Локальным
# максимумом называется такое число в последовательности, которое больше
# своих соседей. Если в последовательности нет двух локальных максимумов,
# выведите число 0. Начальное и конечное значение при этом локальными
# максимумами не считаются.


indexlm = 0
indexprevlm = 0
dindex = 0
dindexmin = int(1e10)
dindexminprint = 0
maxlm = 0
cntwhile = 0

n = int(input())
nprev = n
npreprev = 0
n = int(input())

while n != 0:
    npreprev = nprev
    nprev = n
    n = int(input())
    if n != 0:
        cntwhile += 1
        # maxlm = max(npreprev, nprev, n)
        # print(maxlm1)
        # if maxlm == nprev:
        if nprev > npreprev and nprev > n:
            indexprevlm = indexlm
            indexlm = cntwhile
            dindex = indexlm - indexprevlm
            # print(indexprevlm, indexlm, dindex)
            if dindex < dindexmin and dindex > 1 and indexprevlm > 0:
                dindexmin = dindex
                dindexminprint = dindexmin

# print(indexprevlm, indexlm)
print(dindexminprint)
