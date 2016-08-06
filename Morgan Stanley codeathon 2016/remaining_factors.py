n = int(input())
count = 0
nsq = n ** 2
for f in range(2, n):
    if nsq % f == 0 and n % f != 0:
        count += 1
print(count)
