# Дана строка. Удалите из этой строки все символы @.

# s = 'Bilbo.Baggins@bagend.hobbiton.shire.me'
# s = '1@1'
s = input()
while s.find('@') != -1:
    s = s.replace('@', '')
print(s)
