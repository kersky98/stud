import unittest
import sys


def sdist(t):
    return t[0]


def sindex(t):
    return t[1]


def f1():
    # s = (10,)
    # b = (1, 2, 10)
    # s = (1, 2, 6, 10)
    # b = (7, 3)
    # s = (1, 6, 2, 10)
    # b = (7, 3)
    # s = (1, 6, 2, 10)
    # b = (7, 3, 6, 20)
    # s = (79, 64, 13, 8, 38, 29, 58, 20, 56, 17)
    # b = (53, 19, 20, 85, 82, 39, 58, 46, 51, 69)
    # s = (79, 64, 13, 8, 38)
    # b = (53, 19, 20, 85)
    # ns = 1
    # s = (1,)
    # nb = 1
    # b = (2,)
    # ns = 7
    # s = (1, 22, 23, 24, 25, 30, 30)
    # nb = 9
    # b = (2, 3, 4, 27, 28, 28, 29, 29, 33)
    # 2.354 sec
    # ns = 10
    s = range(1, 10000)
    # nb = 10
    b = range(1, 10000, 4)
    # print(*b)
    ss = []
    for index, item in enumerate(s):
        ss.append((item, index))
    bb = []
    for index, item in enumerate(b):
        bb.append((item, index))

    # print(ss)
    # print(bb)
    # ssorig = ss.copy()
    # bborig = bb.copy()
    # print(ssorig)
    # print(bborig)
    ss.sort(key=sdist)
    bb.sort(key=sdist)
    # print(*ss)
    # print(*bb)

    bbstart = 0
    outlist = []
    for sindex in range(len(ss)):
        scurr = ss[sindex]
        bmin = sys.maxsize
        bminindex = 0
        for bindex in range(bbstart, len(bb)):
            bcurr = bb[bindex]
            bs = abs(bcurr[0] - scurr[0])
            if bs < bmin:
                bmin = bs
                bminindex = bindex
            if bindex > 1 and bmin-bs < 0:
                break
        # outlist.append((sindex, bminindex))
        outlist.append(bminindex)
        bbstart = bminindex

    # print(*outlist)

    outlist1 = []
    for sindex in range(len(ss)):
        a = ss[sindex][1]
        b = bb[outlist[sindex]][1]
        outlist1.append((a, b))

    # print(*outlist1)

    outlist2 = sorted(outlist1, key=sdist)
    # print(*outlist2)
    for sindex in range(len(ss)):
        print(outlist2[sindex][1] + 1, end=' ')
    print()


class MyTest(unittest.TestCase):
#     def test_add(self):
#         self.assertEqual(3, 3)
# 
#     def test_sub(self):
#         self.assertEqual(2, 2)
# 
#     def test_mul(self):
#         self.assertEqual(10, 10)
# 
#     def test_div(self):
#         self.assertEqual(2, 2)
        
    def test_f1(self):
        f1()
        self.assertEqual(2, 2)


if __name__ == '__main__':
    unittest.main()
