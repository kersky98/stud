# Дан список из чисел и индекс элемента в списке k. Удалите из списка элемент
# с индексом k, сдвинув влево все элементы, стоящие правее элемента с индексом
# k. Программа получает на вход список, затем число k. Программа сдвигает все
# элементы,а после этого удаляет последний элемент списка при помощи метода
# pop(). Программа должна осуществлять сдвиг непосредственно в списке, а не
# делать это при выводе элементов. Также нельзя использовать дополнительный
# список.

s = list(map(int, input().split()))
n = int(input())

for index, item in enumerate(s):
    if index > n:
        s[index-1] = s[index]

s.pop()
for item in s:
    print(item, end=' ')
