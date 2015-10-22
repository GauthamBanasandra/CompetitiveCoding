__author__ = 'gauth_000'
for test_cases in range(int(input())):
    string=input()
    match_count=0
    for i in range(len(string)):
        suffix=string[i:]
        k=0
        for j in range(len(suffix)):
            if string[j]==suffix[j]:
                k+=1
            else:
                break
        match_count+=k
    print(match_count)