# Дан список, упорядоченный по неубыванию элементов в нем.Определите, сколько
# в нем различных элементов.

# n = int(input())
m = list(map(int, input().split()))
# k = int(input())

# m = [1, 1, 1, 1, 1]
# k = 160

res = 1
prev = m[0]
for index, item in enumerate(m[1::]):
    if item > prev:
        res += 1
        # print(item)
    prev = item

print(res)
