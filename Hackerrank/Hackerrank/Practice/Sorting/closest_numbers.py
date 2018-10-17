__author__ = 'gauth_000'
n=int(input())
numbers=sorted(list(map(int, input().strip().split())))
num_diff={}
for i in range(len(numbers)-1):
    diff=numbers[i+1]-numbers[i]
    if diff in num_diff:
        num_diff[diff].append((numbers[i], numbers[i+1]))
    else:
        num_diff[diff]=[(numbers[i], numbers[i+1])]
for tuple in num_diff[min(num_diff.keys())]:
    print(tuple[0], tuple[1], end=' ')