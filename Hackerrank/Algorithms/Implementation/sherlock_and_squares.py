import math

__author__ = 'gauth_000'
for i in range(int(input())):
    l, u = map(int, input().strip().split())
    l_=math.ceil(l**0.5)
    u_=math.ceil(u**0.5)
    count = 0
    while l_<=u_:
        if l_**2<=u:
            count+=1
        l_+=1
    print(count)