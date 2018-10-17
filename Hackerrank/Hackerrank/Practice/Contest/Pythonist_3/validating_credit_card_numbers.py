import re

__author__ = 'gauth_000'
for test_cases in range(int(input())):
    string = input()
    valid = True
    if string.find(' ') != -1:
        valid = False
    if valid and (string[0] == '4' or string[0] == '5' or string[0] == '6'):
        if valid and string.find('-') != -1:
            if len(string.split('-')) != 4:
                valid = False
            if valid:
                for num in string.split('-'):
                    if len(num) != 4:
                        valid = False
                        break
        if valid:
            for c in string:
                if c != '-':
                    if c.isalpha():
                        valid = False
                        break
        if valid and len(string.replace('-', '')) != 16:
            valid = False
        if valid:
            numbers = re.findall(r'(\d)(\1+)', string.replace('-', ''))
            for num in numbers:
                if len(num[1]) + 1 > 3:
                    valid = False
                    break
    else:
        valid = False
    print('Valid' if valid else 'Invalid')
