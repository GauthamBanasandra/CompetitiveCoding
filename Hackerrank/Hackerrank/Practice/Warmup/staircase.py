__author__ = 'gauth_000'
height = int(input())
for i in range(height):
    print(' ' * (height - i - 1), end='')
    print('#' * (i + 1))
