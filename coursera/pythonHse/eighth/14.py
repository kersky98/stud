from sys import stdin


class MatrixError(BaseException):
    def __init__(self, Matrix1, Matrix2):
        self.matrix1 = Matrix1
        self.matrix2 = Matrix2


class Matrix:
    def __init__(self, lst):
        self.mylst = []
        for item in lst:
            self.mylst.append(item.copy())

    def __str__(self):
        self.mystr = ''
        for irow, row in enumerate(self.mylst):
            self.mystr += '\t'.join(map(str, row))
            if irow != len(self.mylst)-1:
                self.mystr += '\n'
        return self.mystr

    def size(self):
        nrows = len(self.mylst)
        if nrows > 0:
            ncolumns = len(self.mylst[0])
        else:
            ncolumns = 0
        self.sz = (nrows, ncolumns)
        return self.sz

    def __add__(self, other):
        if self.size() == other.size():
            smylist = []
            nrows = self.size()[0]
            for i in range(nrows):
                smylist.append(
                    list(
                        map(
                            lambda x: x[0] + x[1],
                            zip(self.mylst[i], other.mylst[i])
                            )
                        )
                    )
            return Matrix(smylist)
        else:
            raise MatrixError(self, other)

    def __mul__(self, other):
        smylist = []
        if isinstance(other, int) or isinstance(other, float):
            for item in self.mylst:
                smylist.append(list(map(lambda x: x * other, item)))
        elif isinstance(other, Matrix):
            nrows1, ncols1 = self.size()
            nrows2, ncols2 = other.size()
            if ncols1 == nrows2:
                a = self.mylst
                b = other.mylst
                for i in range(nrows1):
                    tmp = []
                    for k in range(ncols2):
                        c = 0
                        for j in range(ncols1):
                            c += a[i][j]*b[j][k]
                        tmp.append(c)
                    smylist.append(tmp)
            else:
                raise MatrixError(self, other)
        return Matrix(smylist)

    __rmul__ = __mul__

    def transpose(self):
        smylist = []
        nrows, ncols = self.size()
        for j in range(ncols):
            tmp = []
            for i in range(nrows):
                tmp.append(self.mylst[i][j])
            smylist.append(tmp)
        self.__init__(smylist)
        return Matrix(smylist)

    @staticmethod
    def transposed(m):
        smylist = []
        nrows, ncols = m.size()
        for j in range(ncols):
            tmp = []
            for i in range(nrows):
                tmp.append(m.mylst[i][j])
            smylist.append(tmp)
        return Matrix(smylist)


exec(stdin.read())
