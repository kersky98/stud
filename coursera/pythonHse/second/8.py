m = int(input())
n = int(input())
k = int(input())

if (m % k == 0 or n % k == 0 or k % m == 0 or k % n == 0) and \
   (m * n > k and k >= m and k >= n):
    print('YES')
else:
    print('NO')
