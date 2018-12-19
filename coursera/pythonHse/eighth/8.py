from itertools import accumulate

print(
    *list(
        accumulate((1,) + tuple(range(1, int(input())+1)), lambda x, y: x*y)
        )
    )
