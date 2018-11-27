x = int(input())

n = abs(x)
if n % 10 == 1 and n > 20 or n == 1:
    print(str(x), 'korova')
elif (n % 10 == 2 or n % 10 == 3 or n % 10 == 4) and (n < 10 or n > 20):
    print(str(x), 'korovy')
elif n % 10 == 0 or n % 10 == 5 or n % 10 == 6 or n % 10 == 7 or n % 10 == 8 \
 or n % 10 == 9 or n < 20:
    print(str(x), 'korov')
