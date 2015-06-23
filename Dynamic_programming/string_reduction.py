__author__ = 'gauth_000'

def reducible(string):
    i = 0
    index = -1
    replace_char = '\0'
    for j in range(i + 1, len(string)):
        if string[i] != string[j]:
            index = i
            break
        i += 1
    if index != -1:
        if (string[i] == 'a' and string[i + 1] == 'b') or (string[i] == 'b' and string[i + 1] == 'a'):
            replace_char = 'c'
        elif (string[i] == 'b' and string[i + 1] == 'c') or (string[i] == 'c' and string[i + 1] == 'b'):
            replace_char = 'a'
        elif (string[i] == 'c' and string[i + 1] == 'a') or (string[i] == 'a' and string[i + 1] == 'c'):
            replace_char = 'b'
        return index, replace_char
    return None

def reverse(string):
    strrev=[]
    for i in range(len(string)-1, -1, -1):
        strrev.append(string[i])
    return ''.join(strrev)

def reduce(string):
    data = reducible(string)
    while data:
        if data:
            string = string.replace(string[data[0]:data[0] + 2], data[1], 1)
        data = reducible(string)
    return len(string)

for test_cases in range(int(input())):
    string = str(input()).strip()
    print(reduce(string), reduce(reverse(string)))