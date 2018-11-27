# Напишите функцию xor(x, y)
# реализующую функцию "Исключающее ИЛИ" двух логических переменных x и y.
# Функция xor должна возвращать True, если ровно один из ее аргументов x или y,
# но не оба одновременно равны True.

x = int(input())
y = int(input())


def xor(x, y):
    if x != 1 or y != 1:
        res = x or y
    else:
        res = 0
    return res


print(xor(x, y))
