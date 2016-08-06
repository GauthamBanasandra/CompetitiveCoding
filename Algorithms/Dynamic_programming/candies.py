n = candies = int(input().strip())
ratings = [int(input().strip()) for i in range(n)]
for i in range(n - 1):
    if ratings[i + 1] > ratings[i]:
        candies += 1
for i in range(n - 1, 0, -1):
    if ratings[i - 1] > ratings[i]:
        candies += 1
print(candies)
