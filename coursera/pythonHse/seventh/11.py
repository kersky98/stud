# Во входном файле (вы можете читать данные из файла input.txt) записан текст.
# Словом считается последовательность непробельных подряд идущих символов.
# Слова разделены одним или большим числом пробелов или символами конца строки.
# Для каждого слова из этого текста подсчитайте, сколько раз оно встречалось в
# этом тексте ранее.
# Тест 1
# Входные данные:
# one two one tho three
# Вывод программы:
# 0 0 1 0 0
fin = open('input.txt', 'r', encoding='utf8')
s = fin.read().split()
# st = []
# for item in s:
#     cnt = st.count(item)
#     print(cnt, end=' ')
#     st.append(item)

# for i in range(len(s)):
#     cnt = st.count(s[i])
#     st = s[0:i+1]
#     # print(st)
#     print(cnt, end=' ')
ds = dict()
for i in range(len(s)):
    if s[i] in ds:
        print(ds[s[i]], end=' ')
        ds[s[i]] += 1
    else:
        print(0, end=' ')
        ds[s[i]] = 1
