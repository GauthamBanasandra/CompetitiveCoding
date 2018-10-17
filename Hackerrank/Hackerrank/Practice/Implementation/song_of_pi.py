__author__ = 'gauth_000'

pi = '31415926535897932384626433833'
for test_cases in range(int(input())):
    words = str(input()).strip().split()
    pi_match = []
    for word in words:
        pi_match.append(str(len(word)))
    if pi.startswith(''.join(pi_match)):
        print('It\'s a pi song.')
    else:
        print('It\'s not a pi song.')
