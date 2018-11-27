# В условиях предыдущей задачи определите количество школьников, ставших
# победителями в каждом классе. Победителями объявляются все, кто набрал
# наибольшее число баллов по данному классу. Гарантируется, что в каждом
# классе был хотя бы один участник.
# Формат вывода
# Выведите три числа: количество победителей олимпиады по 9 классу,
# по 10 классу, по 11 классу.
fin = open('input.txt', 'r', encoding='utf8')

lst9 = []
lst10 = []
lst11 = []
for item in fin:
    Name, Surname, Class, Scope = \
        item.split()
    cl = int(Class)
    sc = int(Scope)
    if cl == 9:
        # lst9.append((Name, Surname, cl, sc))
        lst9.append(sc)
    elif cl == 10:
        # lst10.append((Name, Surname, cl, sc))
        lst10.append(sc)
    elif cl == 11:
        # lst11.append((Name, Surname, cl, sc))
        lst11.append(sc)

# print(*lst9)
# print(*lst10)
# print(*lst11)

cnt9 = lst9.count(max(lst9))
cnt10 = lst10.count(max(lst10))
cnt11 = lst11.count(max(lst11))
print(cnt9, cnt10, cnt11)
