# Дана строка, состоящая из слов, разделенных пробелами. Определите, сколько
# в ней слов.

# s = 'Hello world'
# s = 'Hello'
# s = 'q w e'
s = input()
count = s.count(' ') + 1
print(count)
