# Во входной строке записана последовательность чисел через пробел. Для
# каждого числа выведите слово YES (в отдельной строке), если это число
# ранее встречалось в последовательности или NO, если не встречалось.
# Формат ввода
# Вводится список чисел. Все числа списка находятся на одной строке.
# Формат вывода
# Выведите ответ на задачу.

lst = list(map(int, input().split()))
# print(*lst)
setl = set()
for index in range(len(lst)):
    if index == 0:
        print('NO')
    else:
        if lst[index] in setl:
            print('YES')
        else:
            print('NO')
    setl.add(lst[index])
# print(setl)

# for index in range(len(lst)):
#     if index == 0:
#         print('NO')
#     else:
#         lst1 = lst[0:index]
#         set1 = set(lst1)
#         # print(set1, set([lst[index]]))
#         # st = set1 & set([lst[index]])
#         if lst[index] in set1:
#             print('YES')
#         else:
#             print('NO')
