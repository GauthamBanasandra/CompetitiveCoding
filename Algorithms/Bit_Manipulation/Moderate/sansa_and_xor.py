# Even though the solution seems to be correct, since it's a brute-force approach, it easily timed-out.
import functools

__author__ = 'gauth_000'


def xor(l):
    return functools.reduce(lambda x, y: x ^ y, l)

for test_cases in range(int(input())):
    input()
    numbers = list(map(int, input().strip().split()))
    res=xor(numbers)
    for n in range(1, len(numbers)):
        i = 0
        j = n
        while j <= len(numbers):
            res^=xor(numbers[i:j])
            i += 1
            j += 1
    print(res)