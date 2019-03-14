import sys

for test_case in range(int(input().strip())):
    n = int(input().strip())
    h = sorted((map(int, input().strip().split())))
    total_strength = sum(h)
    s = 1
    maxP = 0
    for i in range(n - 1):
        s += 1
        try:
            total_strength -= h[i]
        except IndexError:
            print('test case:', test_case)
            print('n=', n, 'i=', i, '\nh:', h)
            sys.exit()
        p = s * total_strength
        if p > maxP:
            maxP = p
    print(maxP)
