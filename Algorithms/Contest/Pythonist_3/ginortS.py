from functools import reduce

__author__ = 'gauth_000'
string = reduce(lambda x, y: x + y, sorted(input()))
try:
    print(reduce(lambda x, y: x + y, filter(lambda x: x.islower(), string)), end='')
    print(reduce(lambda x, y: x + y, filter(lambda x: x.isupper(), string)), end='')
    print(reduce(lambda x, y: x + y, filter(lambda x: x.isdigit() and int(x) % 2, string)), end='')
    print(reduce(lambda x, y: x + y, filter(lambda x: x.isdigit() and not int(x) % 2, string)), end='')
except:
    pass
