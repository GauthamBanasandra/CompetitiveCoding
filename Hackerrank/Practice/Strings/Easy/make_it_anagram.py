__author__ = 'gauth_000'

string_1=input()
string_2=input()
frequency={}
for c in string_1:
    if c in string_2:
        frequency[c]=frequency.get(c, 0)+1
print(len(string_1)+len(string_2)-sum(frequency.values())*2)