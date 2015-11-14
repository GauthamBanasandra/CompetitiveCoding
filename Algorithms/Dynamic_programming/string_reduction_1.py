__author__ = 'gauth_000'

def count_abc(string):
    a=b=c=0
    for char in string:
        if char=='a':
            a+=1
        if char=='b':
            b+=1
        if char=='c':
            c+=1
    return a, b, c

def is_distinct(string):
    c=string[0]
    for char in string:
        if c!=char:
            return False
    return True

for test_cases in range(int(input())):
    string=str(input())
    if is_distinct(string):
        print(len(string))
    else:
        count=count_abc(string)
        if (count[0]%2==0 and count[1]%2==0 and count[2]%2==0) or (count[0]%2!=0 and count[1]%2!=0 and count[2]%2!=0):
            print(2)
        else:
            print(1)