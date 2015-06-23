__author__ = 'gauth_000'

for test_cases in range(int(input())):
    n, s = map(int, str(input()).strip().split())
    a = sorted(list(map(int, str(input()).strip().split())))
    b = sorted(list(map(int, str(input()).strip().split())), reverse=True)
    for i in range(n):
        if a[i] + b[i] < s:
            print('NO')
            break
    else:
        print('YES')
