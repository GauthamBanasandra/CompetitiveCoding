__author__ = 'gauth_000'
import math

for test_cases in range(int(input())):
    n = int(input())
    if n >= 2:
        print(int(math.factorial(n) / (math.factorial(n - 2) * 2)))
    else:
        print(0)
