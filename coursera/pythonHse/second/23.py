# По данному числу N распечатайте все целые степени двойки, не превосходящие\
# N, в порядке возрастания.Операцией возведения в степень пользоваться нельзя!
n = int(input())

i = 0
p = 1
while p <= n:
    k = 0
    p = 1
    while k < i:
        # p = 2**i
        p = 2 * p
        k = k + 1
    if p <= n:
        print(p, end=' ')
    i = i + 1