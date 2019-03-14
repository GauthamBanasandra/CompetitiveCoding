__author__ = 'gauth_000'

n, k=map(int, input().strip().split())
toys=sorted(map(int, input().strip().split()))
amount=0
count=0
for i in range(n):
    if amount+toys[i]<=k:
        amount+=toys[i]
        count+=1
    else:
        break
print(count)