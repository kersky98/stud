# Напишите программу, которая по данному числу n от 1 до 9 выводит на экран
# n флагов. Изображение одного флага имеет размер 4×4 символов, между двумя
# соседними флагами также имеется пустой (из пробелов) столбец. Разрешается
# вывести пустой столбец после последнего флага. Внутри каждого флага должен
# быть записан его номер — число от 1 до n.


def PrintFlag(n):
    for i in range(n):
        print('+___ ', end='')
    print()
    for i in range(n):
        print('|', i+1, ' ', '/ ', sep='', end='')
    print()
    for i in range(n):
        print('|', '_', '_', '\\ ', sep='', end='')
    print()
    for i in range(n):
        print('|    ', end='')
    print()


n = int(input())

PrintFlag(n)
