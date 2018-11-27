# Дана строка. Удалите из нее все символы, чьи индексы делятся на 3.
# Символы строки нумеруются, начиная с нуля.
s = input()
# s = 'Python'
# s = 'Hello'
# sres = s
# print(s[0])
sz = len(s)
index = 0
while index < sz:
    s1 = s[:index]
    s2 = s[index+1:]
    s = s1 + '*' + s2
    index += 3
s = s.replace('*', '')
print(s)
