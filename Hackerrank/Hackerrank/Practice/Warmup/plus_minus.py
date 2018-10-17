__author__ = 'gauth_000'

import math

size = int(input())
positive = 0
negative = 0
zero = 0
for number in list(map(int, str(input()).strip().split())):
    if number > 0:
        positive += 1
    elif number < 0:
        negative += 1
    else:
        zero += 1
print(math.ceil((positive / size) * 1000) / 1000)
print(math.ceil((negative / size) * 1000) / 1000)
print(math.ceil((zero / size) * 1000) / 1000)
