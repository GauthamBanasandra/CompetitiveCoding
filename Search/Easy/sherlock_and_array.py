# Have 2 counters 'left' initialized to 0 and 'right' initialized to the sum of the array. Subtract the current element
# from 'right' and check if 'left'=='right' else subtract the element from 'left'.
__author__ = 'gauth_000'
for test_cases in range(int(input())):
    input()
    numbers = list(map(int, str(input()).strip().split()))
    left = 0
    right = sum(numbers)
    for num in numbers:
        right-=num
        if left==right:
            print('YES')
            break
        left+=num
    else:
        print('NO')