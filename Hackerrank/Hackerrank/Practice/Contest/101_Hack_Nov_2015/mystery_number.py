import collections

__author__ = 'gauth_000'
input()
list_a=collections.Counter(list(map(int, input().strip().split())))
list_b=collections.Counter(list(map(int, input().strip().split())))
for k, v in list_b.items():
    if k in list_a:
        if list_b[k]-list_a[k]!=0:
            print(k)
            break
    else:
        print(k)
        break
