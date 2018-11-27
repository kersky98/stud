# По данному натуральном n вычислите сумму 1²+2²+3²+...+n².

n = int(input())

res = 0
for i in range(1, n+1):
    res += i**2
print(res)
