__author__ = 'gauth_000'
# Incomplete.
input()
numbers = list(map(int, input().strip().split()))
count = 0
for i in range(1, len(numbers)):
    j = i - 1
    k = numbers[i]
    while j >= 0 and numbers[j] >= k:
        numbers[j + 1] = numbers[j]
        j -= 1
    numbers[j + 1] = k
    if i != j:
        count += 1
        print(numbers)
print(count)
