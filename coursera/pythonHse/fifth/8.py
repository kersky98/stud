# По данному натуральному n≤9 выведите лесенку из n ступенек, i-я ступенька
# состоит из чисел от 1 до i без пробелов.
n = int(input())

for i in range(n):
    for j in range(i+1):
        print(j+1, end='')
    print()
