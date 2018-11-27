# Найдите наибольшее значение в списке и индекс последнего элемента, который
# имеет данное значение за один проход по списку, не модифицируя этот список и
# не используя дополнительного списка.

s = list(map(int, input().split()))

nmax = max(s)
ind = 0
itm = 0

for index, item in enumerate(s):
    if item == nmax:
        ind = index
        itm = item

print(itm, ind)
