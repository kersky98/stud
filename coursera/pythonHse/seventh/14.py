# Дан текст. Выведите слово, которое в этом тексте встречается чаще всего. Если
# таких слов несколько, выведите то, которое меньше в лексикографическом
# порядке.
# Тест 1
# Входные данные:
# apple orange banana banana orange
# Вывод программы:
# banana
fin = open('input.txt', 'r', encoding='utf8')
s = fin.read().split()
ds = dict()
for i in range(len(s)):
    if s[i] in ds:
        ds[s[i]] += 1
    else:
        ds[s[i]] = 1
# print(ds)
dsr = dict()
maxval = max(ds.values())
# print(maxval)
for item in ds:
    if ds[item] == maxval:
        dsr[item] = maxval
print(sorted(dsr)[0])
