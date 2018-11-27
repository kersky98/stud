# Напишите программу, которая находит в массиве элемент, самый близкий
# по величине к данному числу

n = int(input())
m = list(map(int, input().split()))
k = int(input())

# n = 5
# m = [1, 2, 3, 4, 5]
# k = 9

mmax = max(m)
mmin = min(m)

if k >= mmax:
    res = mmax
elif k <= mmin:
    res = mmin
else:
    dm = []
    for item in m:
        dm.append(abs(item - k))
    # print(dm)
    dmmin = min(dm)
    dmindex = dm.index(dmmin)
    res = m[dmindex]

print(res)
