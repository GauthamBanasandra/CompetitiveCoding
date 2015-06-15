__author__ = 'gauth_000'

t = int(input())
for i in range(t):
    chocolates = 0
    n, c, m = [int(i) for i in str(input()).strip().split()]#Converts a list of strings separated by white spaces into a list of int
    wrappers = chocolates = n // c
    while wrappers >= m:
        wrappers -= m
        chocolates += 1
        wrappers += 1
    print(chocolates)
