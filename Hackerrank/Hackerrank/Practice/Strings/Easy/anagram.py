__author__ = 'gauth_000'
# The logic used here is, divide the string into two halves. Pick each character from the second half and see if it it
# exists in the first half. If so, delete the character from the first half of the string. The solution is the length of
# the first half of the string after all the deletions.
for i in range(int(input())):
    s=input()
    length=len(s)
    if length%2==0:
        # print(s[:length//2], s[length//2:])
        first_half=list(s[:length//2])
        for c in s[length//2:]:
            if c in first_half:
                first_half.remove(c)
        print(len(first_half))
    else:
        print(-1)