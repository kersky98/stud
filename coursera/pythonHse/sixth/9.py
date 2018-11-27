# Известно, что фамилии всех участников — различны. Сохраните в массивах
# список всех участников и выведите его, отсортировав по фамилии в
# лексикографическом порядке. При выводе указываете фамилию, имя участника
# и его балл.
# Используйте для ввода и вывода файлы input.txt и output.txt с указанием
# кодировки utf8. Например, для чтения откройте файл с помощью
# open('input.txt', 'r', encoding='utf8').
# Входные данные:
# Строки вида "Фамилия Имя НомерШколы Балл".

fin = open('input.txt', 'r', encoding='utf8')
fout = open('output.txt', 'w', encoding='utf8')

lst = []
for item in fin:
    # print(item, end='')
    Name, Surname, Class, Score = \
        item.split()
    lst.append((Name, Surname, Score))

fin.close()
lst.sort(key=lambda x: x[0])
for item in lst:
    print(*item, file=fout)
fout.close()
