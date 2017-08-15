__author__ = 'gauth_000'

stones = int(input())
gemstones = set(input())
for i in range(stones - 1):
    gemstones = gemstones.intersection(input())
print(len(gemstones))
