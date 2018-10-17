# Algorithm is if the size is even number, then the answer is 0 else, it is xor of alternate numbers.
import functools

__author__ = 'gauth_000'


def xor(l):
    return functools.reduce(lambda x, y: x ^ y, l)

for test_cases in range(int(input())):
    length=int(input())
    numbers = list(map(int, input().strip().split()))
    if length%2!=0:
        print(xor(numbers[::2]))
    else:
        print(0)