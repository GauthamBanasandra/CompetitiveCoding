__author__ = 'gauth_000'

for test_cases in range(int(input())):
    print(~int(input()) & 0xFFFFFFFF)#To get 32-bit unsigned integer, we need to mask the sign bit which can be done by anding it with 0xFFFFFFFF
