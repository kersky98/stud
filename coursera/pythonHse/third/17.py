# Дана строка. Найдите в этой строке второе вхождение буквы f, и выведите
# индекс этого вхождения. Если буква f в данной строке встречается только один
# раз, выведите число -1, а если не встречается ни разу, выведите число -2.
# При решении этой задачи нельзя использовать метод count.

# s = 'comfort'
# s = 'coffee'
# s = 'qwerty'

s = input()
i1 = s.find('f')

if i1 < 0:
    print(-2)
else:
    i2 = s.find('f', i1+1)
    if i2 < 0:
        print(-1)
    else:
        print(i2)