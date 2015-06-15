__author__ = 'gauth_000'


def gcd(x, y):
    while x != y:
        if x > y:
            x -= y
        else:
            y -= x
    return x


for test_cases in range(int(input())):
    l, b = [int(i) for i in str(input()).strip().split()]
    dimension = gcd(l, b)
    print(int((l * b) / dimension ** 2))
