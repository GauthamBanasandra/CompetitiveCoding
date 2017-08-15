import functools

__author__ = 'gauth_000'

string = input()
frequency = [string.count(s) for s in set(string)]
if len(string) % 2 != 0:
    print('YES') if len(list(filter(lambda x: x % 2 != 0, frequency))) == 1 else print('NO')
else:
    print('YES') if functools.reduce(lambda x, y: x % 2 == 0 and y % 2 == 0, frequency) else print('NO')
