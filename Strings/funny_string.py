__author__ = 'gauth_000'

for test_cases in range(int(input())):
    string = input()
    n = len(string)
    funny = True
    for i in range(n//2):
        if abs(ord(string[i]) - ord(string[i + 1])) != abs(ord(string[n - i - 1]) - ord(string[n - i - 2])):
            funny = False
            break
    if funny:
        print('Funny')
    else:
        print('Not funny')
