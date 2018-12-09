# Вам дан словарь, состоящий из пар слов. Каждое слово является синонимом к
# парному ему слову. Все слова в словаре различны. Для одного данного слова
# определите его синоним.
# Формат ввода
# Программа получает на вход количество пар синонимов N. Далее следует N строк,
# каждая строка содержит ровно два слова-синонима. После этого следует одно
# слово.
# Формат вывода
# Программа должна вывести синоним к данному слову.
# Примечания
# Эту задачу можно решить и без словарей (сохранив все входные данные в списке)
# но решение со словарем будет более простым.
# Тест 1
# Входные данные:
# 3
# Hello Hi
# Bye Goodbye
# List Array
# Goodbye
# Вывод программы:
# Bye
fin = open('input.txt', 'r', encoding='utf8')
n = int(fin.readline())
ds = dict()
dsr = dict()
for i in range(n):
    key, value = fin.readline().split()
    ds[key] = value
    dsr[value] = key
ssearch = fin.readline().strip()
# print(ds)
# print(ssearch)
# print(ds[ssearch])
if ssearch in ds:
    print(ds[ssearch])
else:
    print(dsr[ssearch])
