__author__ = 'gauth_000'

for test_cases in range(int(input())):
    string = list(input())
    unique_string = ['0']
    for char in string:
        if unique_string[-1] != char:
            unique_string.append(char)
    print(len(string) - len(unique_string[1:]))
