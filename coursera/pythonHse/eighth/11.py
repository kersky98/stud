from sys import stdin


class Matrix:
    def __init__(self, lst):
        self.mylst = []
        for item in lst:
            self.mylst.append(item.copy())

    def __str__(self):
        self.mystr = ''
        for irow, row in enumerate(self.mylst):
            self.mystr += '\t'.join(map(str, row))
#             for index, item in enumerate(row):
#                 self.mystr += str(item)
#                 if index != len(row)-1:
#                     self.mystr += '\t'
            if irow != len(self.mylst)-1:
                self.mystr += '\n'
        return self.mystr

    def size(self):
        nrows = len(self.mylst)
        if nrows > 0:
            ncolumns = len(self.mylst[0])
        else:
            ncolumns = 0
        self.size = (nrows, ncolumns)
        return self.size


exec(stdin.read())
# m = Matrix([[2, 2], [0, 0], [1, 1]])

# print(str(m))
