__author__ = 'gauth_000'

for test_cases in range(int(input())):
    number = input()
    count = 0
    for digit in number:
        if int(digit) != 0 and int(number) % int(digit) == 0:
            count += 1
    print(count)
