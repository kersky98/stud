# Последовательность состоит из натуральных чисел и завершается числом 0.
# Определите, какое количество элементов этой последовательности,
# равны ее наибольшему элементу.

n = int(input())
maxcurr = n
cnt = 1
while n != 0:
    n = int(input())
    if n > maxcurr and n != 0:
        maxcurr = n
        cnt = 1
    elif n == maxcurr and n != 0:
        cnt += 1

print(cnt)
