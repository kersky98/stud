# Каждый из N школьников некоторой школы знает Mᵢ языков. Определите, какие
# языки знают все школьники и языки, которые знает хотя бы один из школьников.
# Формат ввода
# Первая строка входных данных содержит количество школьников N. Далее идет N
# чисел Mᵢ, после каждого из чисел идет Mᵢ строк, содержащих названия языков,
# которые знает i-й школьник. Длина названий языков не превышает 1000 символов,
# количество различных языков не более 1000. 1≤N≤1000, 1≤Mᵢ≤500.
# Формат вывода
# В первой строке выведите количество языков, которые знают все школьники.
# Начиная со второй строки - список таких языков. Затем - количество языков,
# которые знает хотя бы один школьник, на следующих строках -
# список таких языков.

fin = open('input.txt', 'r', encoding='utf8')
n = int(fin.readline().replace('\n', ''))
# lst = []
setall = set()
setone = set()
for i in range(n):
    ni = int(fin.readline().replace('\n', ''))
    lang = []
    for j in range(ni):
        lang.append(fin.readline().replace('\n', ''))
    # print(ni, lang)
    setall |= set(lang)
    if i != 0:
        setone &= set(lang)
    else:
        setone = set(lang)
    # lst.append((ni, lang))
# print(*lst)
print(len(setone))
for item in setone:
    print(item)
print(len(setall))
for item in setall:
    print(item)
