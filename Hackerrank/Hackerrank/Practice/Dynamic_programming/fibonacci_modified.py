__author__ = 'gauth_000'

a, b, n = [int(num) for num in str(input()).strip().split()]
for i in range(n - 2):
    c = b * b + a
    a = b
    b = c
print(c)
