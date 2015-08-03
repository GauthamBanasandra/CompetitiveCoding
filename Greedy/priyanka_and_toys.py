__author__ = 'gauth_000'

n = int(input())
toys = sorted(list(map(int, str(input()).strip().split())))
cost = 0
i = 0
while i < n:
    cost += 1
    min_weight = toys[i]
    max_weight = toys[i] + 4
    while i+1 < n and min_weight <= toys[i + 1] <= max_weight:
        i += 1
    i += 1
print(cost)
