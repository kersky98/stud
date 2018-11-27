a = int(input())
b = int(input())
n = int(input())

cost = a * 100 + b
scost = cost * n

print(scost // 100, scost % 100)
