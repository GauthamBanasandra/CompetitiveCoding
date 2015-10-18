import functools

__author__ = 'gauth_000'

def max_sum_contiguous(numbers):
    negative=True
    intermediate=cumulative=0
    for num in numbers:
        if num>=0:
            negative=False
        intermediate+=num
        if intermediate<0:
            intermediate=0
        if cumulative<intermediate:
            cumulative=intermediate
    if negative:
        return max(numbers)
    return cumulative

def max_sum_discontiguous(numbers):
    try:
        return functools.reduce(lambda x, y:x+y, filter(lambda x:x>=0, numbers))
    except TypeError:
        return max(numbers)

for i in range(int(input())):
    input()
    numbers=list(map(int, input().strip().split()))
    print(max_sum_contiguous(numbers), max_sum_discontiguous(numbers))