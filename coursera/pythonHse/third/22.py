# Дана строка. Замение в этой строке все появления буквы h на букву H,
# кроме первого и последнего вхождения.
# s = 'In the hole in the ground there lived a hobbit'

s = input()
istart = s.find('h')
iend = s.rfind('h')
ssub1 = s[:istart+1]
ssub2 = s[istart+1:iend]
ssub3 = s[iend:]

ssub2 = ssub2.replace('h', 'H')
print(ssub1+ssub2+ssub3)
