# Петя перешёл в другую школу. На уроке физкультуры ему понадобилось определить
# своё место в строю.Помогите ему это сделать.

# n = int(input())
m = list(map(int, input().split()))
k = int(input())

# m = [165, 163, 160, 160, 157, 157, 155, 154]
# k = 150

res = len(m)
for index, item in enumerate(m):
    if item < k:
        res = index
        break

print(res+1)
