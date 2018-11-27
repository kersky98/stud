# Дано целое число, не меньшее 2.\
# Выведите его наименьший натуральный делитель, отличный от 1.
n = int(input())

i = n
nd = i
while True:
    if i < 2:
        break
    if n % i == 0:
        nd = i
    i = i - 1
print(nd)
