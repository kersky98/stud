# Дана строка, в которой буква h встречается как минимум два раза.
# Выведете измененную строку: повторите последовательность символов,
# заключенную между первым и последним появлением буквы h два раза
# (сами буквы h не входят в повторяемый фрагмент, т.е. их повторять не надо).

s = input()
# s = 'In the hole in the ground there lived a hobbit'

hstart = s.find('h')
hend = len(s) - s[::-1].find('h') - 1
# print(hstart, hend)
ssub1 = s[:hend]
ssub2 = s[hstart+1:]
print(ssub1+ssub2)
