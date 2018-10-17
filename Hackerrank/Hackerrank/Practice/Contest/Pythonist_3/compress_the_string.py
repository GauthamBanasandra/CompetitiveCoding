import re

__author__ = 'gauth_000'
compression = re.findall(r'(\d)(\1*)', input())
for t in compression:
    print('(' + (str(1) if not len(t[1]) else str(len(t[1]) + 1)) + ', ' + t[0] + ')', end=' ')
