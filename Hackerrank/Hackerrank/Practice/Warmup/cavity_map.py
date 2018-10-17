__author__ = 'gauth_000'

map = []
for dimension in range(int(input())):
    map.append(list(str(input()))) #Convert each string into a list.
for i in range(1, len(map) - 1):
    for j in range(1, len(map[i]) - 1):
        if (map[i][j] > map[i][j + 1] and
                    map[i][j] > map[i][j - 1] and
                    map[i][j] > map[i - 1][j] and
                    map[i][j] > map[i + 1][j]):
            map[i][j] = 'X'
for row in map:
    for cell in row:
        print(cell, end='')
    print()
# print(map)
