x1, v1, x2, v2 = map(int, input().strip().split(' '))
if x1 < x2 and v1 < v2 or v1==v2:
    print('NO')
# elif (x1%2==0 and x2%2==0) or (x1%2!=0 and x2%2!=0):
else:
    print('YES')
