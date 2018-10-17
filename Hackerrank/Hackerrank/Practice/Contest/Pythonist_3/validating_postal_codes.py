import re

__author__ = 'gauth_000'
string='552523'
s=re.search(r'(\d)\d\1', string)
print(s.group())