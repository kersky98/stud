# Исполнитель “Раздвоитель” преобразует натуральные числа.
# У него есть две команды: “Вычесть 1” и “Разделить на 2”, первая команда
# уменьшает число на 1, вторая команда уменьшает число в два раза,
# если оно чётное,иначе происходит ошибка. Дано два натуральных числа
# A и B (A>B). Напишите алгоритм для Раздвоителя, который преобразует число A
# в число B и при этом содержит минимальное число команд. Команды алгоритма
# нужно выводить по одной в строке, первая команда обозначается, как -1,
# вторая команда как :2.

a = int(input())
b = int(input())

n = a

while n > b:
    # print(n, b)
    if n / b >= 2 and n % 2 == 0:
        # то делим
        n = n // 2
        print(':2')
    else:
        # отнимаем
        n = n - 1
        print('-1')

# print(n)
