# Найдите и выведите все двузначные числа, которые равны удвоенному
# произведению своих цифр.

ns = 10
ne = 100

tt = tuple()

for i in range(ns, ne):
    t = tuple(str(i))
    zm = 2 * int(t[0]) * int(t[1])
    if i == zm:
        # print(i)
        tt += (zm, )

for i in range(len(tt)):
    print(tt[i])
