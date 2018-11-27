# Последовательность Фибоначчи определяется так:
# F[0] = 0, F[1] = 1, ..., F[n] = F[n-1] + F[n-2].
# По данному числу n определите n-е число Фибоначчи F[n].

n = int(input())
fib = 1
fibprev = 0
cnt = 0
while n > cnt + 1:
    fibtmp = fib
    fib = fibprev + fib
    fibprev = fibtmp
    cnt += 1

print(fib)
