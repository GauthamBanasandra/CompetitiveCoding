__author__ = 'gauth_000'
import math

n, k=map(int, str(input()).strip().split())
flo=sorted(map(int, str(input()).strip().split()))
print('sorted flo: ', flo)
flo_cost=[]
each=math.ceil(n/k)
count=0
for i in range(n):
    count+=1
    if count%each==0:
        j=i
        while count!=0:
            flo_cost.append(flo[j])
            j-=1
            count-=1
if len(flo)%each!=0:
    for i in range(n-1, n-n%each-1, -1):
        flo_cost.append(flo[i])
print('flo_cost: ', flo_cost)
flo=flo_cost
x=0
cost=0
for i in range(n):
    cost+=(x%each+1)*flo[i]
    #print('cost: ', cost, ' x: ', x)
    x+=1
print(cost)