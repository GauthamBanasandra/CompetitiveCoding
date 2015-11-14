__author__ = 'gauth_000'
n=int(input())
k=int(input())-1
numbers=sorted([int(input()) for i in range(n)])
min=max(numbers)
i=0
while i+k<n:
    x=numbers[i+k]-numbers[i]
    if x<min:
        min=x
    i+=1
print(min)