a = list(map(int, str(input()).strip().split()))
b = list(map(int, str(input()).strip().split()))
alice = bob = 0
for i in range(len(a)):
    if a[i] > b[i]:
        alice += 1
    elif b[i] > a[i]:
        bob += 1

print(alice, bob)
