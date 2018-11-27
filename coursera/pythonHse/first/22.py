n = input()
# n = '002'
len1 = n.__len__()
# print(n[0], len)
# print(n)

centr = len1 // 2
num = (len1+1) // 2

true = 0
false = 0

for i in range(num):
    j = centr-1
    if j >= 0:
        # print(n[centr + i], n[j - i])
        if n[centr + i] == n[j - i]:
            true += 1
        else:
            false = 1
            break
print((false + 1) % 2)
