from functools import reduce
from itertools import permutations

print(
    '\n'.join(
        map(
            str,
            (
                map(
                    lambda x: reduce(lambda a, b: a+b, x),
                    (permutations(map(str, range(1, int(input())+1))))
                    )
                )
            )
        )
    )
