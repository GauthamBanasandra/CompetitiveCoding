__author__ = 'gauth_000'

number = int(input())
factorial = 1
while number >= 1:
    factorial *= number
    number -= 1
print(factorial)
