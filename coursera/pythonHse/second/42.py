# Дана последовательность натуральных чисел, завершающаяся числом 0.
# Определите, какое наибольшее число подряд идущих элементов этой
# последовательности равны друг другу.

n = int(input())
cnt = 0
cntprev = 0

while n != 0:
    nprev = n
    n = int(input())
    if n != 0:
        if nprev == n:
            cnt += 1
            # cntprev = 0
        else:
            if cnt != 0:
                if cnt > cntprev:
                    cntprev = cnt
            cnt = 0

if cntprev == 0:
    print(cnt + 1)
else:
    print(cntprev + 1)
