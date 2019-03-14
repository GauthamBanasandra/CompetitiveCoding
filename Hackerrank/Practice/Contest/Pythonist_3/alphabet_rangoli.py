__author__ = 'gauth_000'
n = int(input())

if n == 1:
    print('a')
else:
    rangoli = list(list())
    for i in range(2 * n - 1):
        line = list()
        for j in range(4 * n - 3):
            line.append('-')
        rangoli.append(line)

    n = len(rangoli)
    k = m = len(rangoli[0])
    l = 0
    for i in range(n // 2, n):
        c = 97 + l
        for j in range(m // 2, k, 2):
            rangoli[i][j] = chr(c)
            c += 1
        k -= 2
        l += 1

    for i in range(n // 2, n):
        # print(i)
        rangoli[i][:m // 2] = rangoli[i][m // 2 + 1:][::-1]

    for i in range(n // 2 + 1, n):
        rangoli[n - i - 1] = rangoli[i]

    for i in range(n):
        for j in range(m):
            print(rangoli[i][j], end='')
        print()
