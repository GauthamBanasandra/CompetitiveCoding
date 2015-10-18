__author__ = 'gauth_000'
n, k=map(int, input().strip().split())
c=sorted(map(int, input().strip().split()))[::-1]
x=[0 for i in range(k)]
cost=0
for i in range(n):
    x[i%k]+=1
    cost+=c[i]*x[i%k]
print(cost)