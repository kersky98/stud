# В списке все элементы попарно различны. Поменяйте местами минимальный и
# максимальный элемент этого списка.

m = list(map(int, input().split()))
# m = [3, 4, 5, 2, 1]

mmax = max(m)
mmin = min(m)
minindex = m.index(mmin)
maxindex = m.index(mmax)
m[minindex] = mmax
m[maxindex] = mmin
print(*m)
