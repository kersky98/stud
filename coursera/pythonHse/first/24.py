a = int(input())
b = int(input())

# a = 10
# b = 3

t = a % b
t = (t + 2) % (t + 1)
# print(t)

print('YES'*(1-t) + 'NO'*t)
