# Дана строка, в которой буква h встречается минимум два раза. Удалите из
# этой строки первое и последнее вхождение буквы h, а также все символы,
# находящиеся между ними.
# s = 'In the hole in the ground there lived a hobbit'
# s = 'qwertyhasdfghzxcvb'

s = input()
hstart = s.find('h')
hend = len(s) - s[::-1].find('h')
# print(hstart, hend)
ssub1 = s[:hstart]
ssub2 = s[hend:]
print(ssub1+ssub2)
