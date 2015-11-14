__author__ = 'gauth_000'

for test_cases in range(int(input())):
    m=int(input())
    n=int(input())
    cost=list(map(int, str(input()).strip().split()))
    for i in range(n):
        for j in range(i+1, n):
            if cost[i]+cost[j]==m:
                print(i+1, j+1)
                break