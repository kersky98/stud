# По данному числу n вычислите сумму 1+(1 / 2²)+(1 / 3²)+...+(1 / n²).

n = int(input())

i = 1

s = 1

while i < n:
    s += 1 / (i + 1)**2
    i += 1

print(s)