__author__ = 'gauth_000'
import math

n, k=map(int, str(input()).strip().split())
c=sorted(map(int, str(input()).strip().split()))
c_temp=[]
each=math.ceil(n/k)
m=0
while m<=k:
    m+=each
    for p in range(m-1, m-each-1, -1):
        if p<len(c):
            c_temp.append(c[p])

print('c_temp: ', c_temp)
# c=c_temp
# i=0
# cost=0
# for person in range(k):
#     for x in range(each):
#         if i<n:
#             try:
#                 cost+=(x+1)*c[i]
#                 i+=1
#             except:
#                 pass
# print(cost)