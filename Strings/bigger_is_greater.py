__author__ = 'gauth_000'

for test_cases in range(int(input())):
    string = list(str(input()))
    n = len(string)
    i = n - 2

    def swap(i, j):
        t = string[i]
        string[i] = string[j]
        string[j] = t


    while i != -1 and not (string[i] < string[i + 1]):
        i -= 1
    if i == -1:
        print('no answer')
    else:
        if i == n - 2:
            j = n - 1
            swap(i, j)
        else:
            # p = 1000000000000000000000000000
            # for j in range(i + 1, n):
            #     if string[j] > string[i] and ord(string[j]) < p:
            #         l = j
            #         p = ord(string[j])
            j=n-1
            while string[j]<=string[i-1]:
                j-=1
            swap(i, j)
            string[i + 1:] = string[i + 1:][::-1]
        print(''.join(string))
