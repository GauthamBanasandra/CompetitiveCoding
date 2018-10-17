__author__ = 'gauth_000'

diff = int(str(input()).split()[1])
numbers = sorted([int(i) for i in str(input()).strip().split()])

def search(key):
    l = 0
    h = len(numbers) - 1
    while l <= h:
        m = (l + h) // 2
        if numbers[m] == key:
            return True
        elif numbers[m] < key:
            l = m + 1
        else:
            h = m - 1
    return False

count = 0
for num in numbers:
    if search(num + diff):
        count += 1
print(count)
