# Дан список чисел. Определите, сколько в этом списке элементов, которыебольше
# двух своих соседей и выведите количество таких элементов.

s = list(map(int, input().split()))

p = list()


def sign(a):
    if a > 0:
        return 1
    elif a < 0:
        return -1
    else:
        return 0


cnt = 0
for index, item in enumerate(s):
    if index > 1:
        if s[index] < s[index-1] > s[index-2]:
            cnt += 1

print(cnt)
