# Переставьте цифры числа в обратном порядке .
n = input()
sz = n.__len__()
i = sz - 1

while i >= 0:
    print(n[i], end='')
    i -= 1
