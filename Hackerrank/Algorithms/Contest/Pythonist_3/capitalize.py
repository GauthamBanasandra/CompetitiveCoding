__author__ = 'gauth_000'
string = list(input())
space = True
for i in range(len(string)):
    if string[i] == ' ':
        space = True
    elif space:
        space = False
        string[i] = string[i].upper()
print(''.join(string))
