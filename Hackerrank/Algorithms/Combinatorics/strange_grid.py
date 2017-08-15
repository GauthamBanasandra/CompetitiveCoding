__author__ = 'gauth_000'

row_column = [int(num) for num in str(input()).strip().split()]
row = row_column[0] - 1
column = row_column[1] - 1
print(10 * (row // 2) + row % 2 + column * 2)
