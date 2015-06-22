__author__ = 'gauth_000'

matrix = []
for size in range(int(input())):
    matrix.append([int(i) for i in str(input()).strip().split()])
left_diag_sum = 0
# print('length of matrix: ', len(matrix))
for i in range(len(matrix)):
    left_diag_sum += matrix[i][i]
    # print('left diag sum: ', left_diag_sum)
right_diag_sum = 0
j = 0
for i in range(len(matrix) - 1, -1, -1):
    right_diag_sum += matrix[j][i]
    j += 1
    # print('right diag sum: ', right_diag_sum)
print(abs(left_diag_sum - right_diag_sum))
