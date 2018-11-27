h = int(input())
a = int(input())
b = int(input())
# a = 3
# b = 2
# h = 10
# a = 9
# b = 1
# h = 10

# d = a-b
# print((h + a - 1) // a)
# print((h + b - 1) // b)
# t = ((h-a+1) // d) + ((a+a-b)//h)
# print(t)

step = a - b
days = ((h - a) / step + 1)
k = days % 1
# Если days - целое, то k=0, иначе k<>0
k = (k + 2) // (k + 1)
# Если days - целое, то k=2, иначе k=1
k = k % 2
# Если days - целое, то k=0, иначе k=1
print(int(days // 1 + k))
