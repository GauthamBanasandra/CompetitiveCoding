__author__ = 'gauth_000'

for i in range(int(input())):
    string=input().strip().split()
    if string[0]=='hackerrank' and string[-1]=='hackerrank':
        print(0)
    elif string[0]=='hackerrank':
        print(1)
    elif string[-1]=='hackerrank':
        print(2)
    else:
        print(-1)