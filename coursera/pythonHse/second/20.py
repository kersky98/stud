# В кафе мороженое продают по три шарика и по пять шариков.\
# Можно ли купить ровно k шариков мороженого?

k = int(input())

n1 = 3
n2 = 5
s = n1 + n2
r = n2 - n1
p = n1 * n2

norm = (k >= n1) and\
 (k % n1 == 0 or k % n2 == 0 or k % s == 0 or
  (k - n1) % n2 == 0 or (k - n2) % n1 == 0 or
  (k - n1) % s == 0 or (k - n2) % s == 0 or
  (k % s) % n1 == 0 or (k % s) % n2 == 0 or
  (k > s and ((k - (k // n2 - 1) * n2) % n1 or (k - (k // n1 - 1) * n1) % n2)))

norm1 = (k >= n1) and k != 4 and k != 7

if norm1:
    print('YES')
else:
    print('NO')
