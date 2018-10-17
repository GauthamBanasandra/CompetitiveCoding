__author__ = 'gauth_000'

for test_cases in range(int(input())):
    b, w = map(int, str(input()).strip().split())
    x, y, z = map(int, str(input()).strip().split())
    print(min(b * x + w * y, b * x + w * (x + z), b * (y + z) + w * y))
