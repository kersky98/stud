print(
    len(
        list(
            filter(lambda x: x is True,
                   map(
                       lambda x: int(input()) == 0, range(int(input()))
                       )
                   )
            )
        ) > 0
    )
