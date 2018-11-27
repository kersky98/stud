# По данному натуральному числу N выведите такое наименьшее целоечисло k,\
# что 2ᵏ≥N.
n = int(input())

k = 0
while True:
    i = 0
    p = 1
    while i < k:
        p = 2 * p
        i = i + 1
    if p >= n:
        print(k)
        break
    k = k + 1
    if k > 1000:
        break
