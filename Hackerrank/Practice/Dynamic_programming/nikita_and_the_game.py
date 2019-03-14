def get_points(numbers, r_sum):
    l_sum = 0
    num_size = len(numbers)
    if num_size == 1:
        return 0
    if r_sum == 0:
        return num_size - 1
    for i in range(num_size):
        l_sum += numbers[i]
        r_sum -= numbers[i]
        if l_sum == r_sum:
            return 1 + max(get_points(numbers[:i + 1], l_sum), get_points(numbers[i + 1:], r_sum))
    return 0


for test_case in range(int(input().strip())):
    n = int(input().strip())
    a = list(map(int, input().strip().split(' ')))
    print(get_points(a, sum(a)))
