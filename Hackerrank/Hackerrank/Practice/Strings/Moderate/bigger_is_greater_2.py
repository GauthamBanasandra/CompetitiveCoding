__author__ = 'gauth_000'
# incorrect.
for i in range(int(input())):
    s=list(input())
    temp_s=''.join(s)
    i=len(s)-2
    j=i+1
    while i>=0 and s[i]>s[i+1]:
        i-=1
    while i>=0 and s[i]>s[j]:
        j-=1
    s[i], s[j]=s[j], s[i]
    s[i+1:]=s[i+1:][::-1]
    # print(s, temp_s)
    s=''.join(s)
    print(''.join(s) if str(s)!=temp_s else 'no answer')