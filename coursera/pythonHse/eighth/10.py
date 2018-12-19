n = 9
res = True
res1 = True
tn = n
while True:
    r = tn % 2
    if r == 0:
        res = False
        break
    else:
        if r == 1:
            res = True
            break
        tn = r


def rem(x):
    r = x % 2
    if r == 0:
        res1 = False
        return
    elif r == 1:
        res1 = True
        return
    rem(r)


print(res)
rem(n)
print(res1)
# print(
#     *list(
#         filter(
#             lambda x1:
#             len(list(filter(lambda x: x1 % x == 0, range(2, x1)))) == 0,
#             list(range(2, int(input())+1))
#             )
#         )
#     )
