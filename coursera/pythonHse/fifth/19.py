# Выведите значение наименьшего нечетного элемента списка, гарантируется,
# что хотя бы один нечётный элемент в списке есть.

s = list(map(int, input().split()))

smin = min(s)
while smin % 2 == 0:
    stmp = s.remove(smin)
    smin = min(s)

print(smin)
