__author__ = 'gauth_000'

for i in range(int(input())):
    pan=input()
    is_pan=True
    for j in range(5):
        if not pan[j].isalpha():
            is_pan=False
    for k in range(5):
        if pan[j].islower():
            is_pan=False
    for l in range(5, 9):
        if not pan[l].isdigit():
            is_pan=False
    if not pan[-1].isalpha():
        is_pan=False
    print('YES') if is_pan else print('NO')