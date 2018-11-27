# Дано натуральное число N. Выведите слово YES, если число N является\
# точной степенью двойки, или слово NO в противном случае.\
# Операцией возведения в степень пользоваться нельзя!
n = int(input())

i = 0
p = 1
is2 = False
while p <= n:
    k = 0
    p = 1
    is2 = False
    while k < i:
        # p = 2**i
        p = 2 * p
        k = k + 1
    if p == n:
        is2 = True
        break
    # print(p, n)
    i = i + 1

if is2:
    print('YES')
else:
    print('NO')
