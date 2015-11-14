__author__ = 'gauth_000'

string = str(input())
pangram = True
for i in range(26):
    if chr(ord('a') + i) not in string.lower():
        pangram = False
        break
if pangram:
    print('pangram')
else:
    print('not pangram')
