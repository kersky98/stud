# Дана последовательность натуральных чисел, завершающаяся число 0.
# Определите наибольшую длину монотонного фрагмента последовательности
# (то есть такого фрагмента, где все элементы либо больше предыдущего,
# либо меньше).

n = int(input())
cntup = 0
cntupprev = 0
cntdown = 0
cntdownprev = 0

while n != 0:
    nprev = n
    n = int(input())
    if n != 0:
        if nprev < n:
            cntup += 1
            if cntdown != 0:
                if cntdown > cntdownprev:
                    cntdownprev = cntdown
            cntdown = 0
        else:
            if cntup != 0:
                if cntup > cntupprev:
                    cntupprev = cntup
            cntup = 0
            if nprev > n:
                cntdown += 1

nmax = max(cntup, cntupprev, cntdown, cntdownprev)
print(nmax + 1)

# if cntup > cntupprev:
#     print(cntup + 1)
# else:
#     print(cntupprev + 1)
