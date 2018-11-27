a = int(input())
b = int(input())

# a = 4
# b = 4

# c = (a - b)
# c = int((c*c)**0.5)
# print(c)
# d = (a + b + 2) // c
# print(d)
# cmp = a * ((a-d) % 2) + b * ((b-d) % 2)

n = a // b
t = (n + 2) % (n + 1)
# print(t)

cmp = a * t + b * (1 - t)
print(cmp)
