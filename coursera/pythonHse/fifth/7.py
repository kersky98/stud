# Дано несколько чисел. Подсчитайте, сколько из них равны нулю, и выведите
# это количество.
n = int(input())

# res = tuple()
k = 0
for i in range(n):
    m = int(input())
    # res += (m, )
    if m == 0:
        k += 1

print(k)
