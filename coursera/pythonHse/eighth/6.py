print(
    *list(
        map(
            lambda x: (x[0] + x[1]) % 2,
            list(
                zip(
                    map(int, input().split()),
                    map(int, input().split()))
                )
            )
        )
    )
