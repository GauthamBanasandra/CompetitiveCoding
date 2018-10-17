__author__ = 'gauth_000'

for test_cases in range(int(input())):
    num = int(input())
    a, b, c = 0, 1, 1
    fibo = False
    if num == 0 or num == 1:
        fibo = True
    while c <= num:
        a = b
        b = c
        c = a + b
        if c == num:
            fibo = True
            break
    if fibo:
        print('IsFibo')
    else:
        print('IsNotFibo')
