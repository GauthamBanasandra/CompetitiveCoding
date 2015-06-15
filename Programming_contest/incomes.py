__author__ = 'gauth_000'

def search(array, key):
    l=0
    h=len(array)-1
    while l<h:
        m=(l+h)//2
        if array[m]==key:
            return m
        elif key>=array[m]:
            l=m+1
        else:
            h=m-1
    return m

incomes = []
for n in range(int(input())):
    incomes.append(int(input()))
incomes.sort()
queries = []
for x in range(int(input())):
    queries.append(int(input()))
'''print('incomes: ', incomes)
print('queries: ', queries)'''
for query in queries:
    if incomes[-1]<query:
        print(len(incomes))
    elif incomes[0]>=query:
        print(0)
    else:
        index=search(incomes, query)
        while incomes[index]>=query:
            index-=1
        print(index+1)
#print(search(incomes, 2))