# Штаб гражданской обороны Тридесятой области решил обновить план спасения на
# случай ядерной атаки. Известно, что все n селений Тридесятой области
# находятся вдоль одной прямой дороги. Вдоль дороги также расположены m
# бомбоубежищ, в которых жители селений могут укрыться на случай ядерной атаки.
# Чтобы спасение в случае ядерной тревоги проходило как можно эффективнее,
# необходимо для каждого селения определить ближайшее к нему бомбоубежище.
# Формат ввода
# В первой строке вводится число n - количество селений (1 <= n <= 100000).
# Вторая строка содержит n различных целых чисел, i-е из этих чисел задает
# расстояние от начала дороги до i-го селения. В третьей строке входных данных
# задается число m - количество бомбоубежищ (1 <= m <= 100000). Четвертая
# строка содержит m различных целых чисел, i-е из этих чисел задает расстояние
# от начала дороги до i-го бомбоубежища. Все расстояния положительны и не
# превышают 10⁹. Селение и убежище могут располагаться в одной точке.
# Формат вывода
# Выведите n чисел - для каждого селения выведите номер ближайшего к нему
# бомбоубежища. Бомбоубежища пронумерованы от 1 до m в том порядке, в котором
# они заданы во входных данных.
# Указание
# Создайте список кортежей из пар (позиция селения, его номер в исходном
# списке), а также аналогичный список для бомбоубежищ. Отсортируйте эти списки.
# Перебирайте селения в порядке возрастания.
# Для селения ближайшими могут быть два соседних бомбоубежища, среди них надо
# выбрать ближайшее. При переходе к следующему селению не обязательно искать
# ближайшее бомбоубежище с самого начала. Его можно искать начиная с позиции,
# найденной для предыдущего города.
# Для хранения ответа используйте список, где индекс будет номером селения,
# а по этому индексу будет запоминаться номер бомбоубежища.
import sys

ns = int(input())
s = list(map(int, input().split()))
nb = int(input())
b = list(map(int, input().split()))


def sdist(t):
    return t[0]


def sindex(t):
    return t[1]


# ns = 4
# s = (1, 2, 6, 10)
# nb = 2
# b = (7, 3)
# ns = 1
# s = (1,)
# nb = 1
# b = (2,)
# ns = 10
# s = (79, 64, 13, 8, 38, 29, 58, 20, 56, 17)
# nb = 10
# b = (53, 19, 20, 85, 82, 39, 58, 46, 51, 69)
# ns = 7
# s = (1, 22, 23, 24, 25, 30, 30)
# nb = 9
# b = (2, 3, 4, 27, 28, 28, 29, 29, 33)

ss = []
for index, item in enumerate(s):
    ss.append((item, index))
bb = []
for index, item in enumerate(b):
    bb.append((item, index))

# print(ss)
# print(bb)
# ssorig = ss.copy()
# bborig = bb.copy()
# print(ssorig)
# print(bborig)
ss.sort(key=sdist)
bb.sort(key=sdist)
# print(*ss)
# print(*bb)

bbstart = 0
outlist = []
for sindex in range(len(ss)):
    scurr = ss[sindex]
    bmin = sys.maxsize
    bminindex = 0
    for bindex in range(bbstart, len(bb)):
        bcurr = bb[bindex]
        bs = abs(bcurr[0] - scurr[0])
        if bs < bmin:
            bmin = bs
            bminindex = bindex
        if bindex > 1 and bmin-bs < 0:
            break
    # outlist.append((sindex, bminindex))
    outlist.append(bminindex)
    bbstart = bminindex

# print(*outlist)

outlist1 = []
for sindex in range(len(ss)):
    a = ss[sindex][1]
    b = bb[outlist[sindex]][1]
    outlist1.append((a, b))

# print(*outlist1)

outlist2 = sorted(outlist1, key=sdist)
# print(*outlist2)
for sindex in range(len(ss)):
    print(outlist2[sindex][1] + 1, end=' ')
print()