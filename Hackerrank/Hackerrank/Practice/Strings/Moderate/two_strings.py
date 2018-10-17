__author__ = 'gauth_000'
for test_cases in range(int(input())):
    str1=input()
    str2=input()
    if len(set(str1).intersection(set(str2)))>0:
        print('YES')
    else:
        print('NO')