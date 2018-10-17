__author__ = 'gauth_000'
length=int(input())
numbers=list(map(int, input().strip().split()))
# length=4
# numbers=[2, 3, 1, 4]
odd_numbers=[]
even_numbers=[]
for number in numbers:
    odd_numbers.append(number) if number&1 else even_numbers.append(number)
odd_numbers.sort()
even_numbers.sort()
numbers.insert(0, 'x')
# print(numbers)
# print(even_numbers)
# print(odd_numbers)
swaps=odd_idx=even_idx=0
for i in range(1, length+1):
    if i&1:
        if odd_numbers[odd_idx]!=numbers[i]:
            odd_idx_swap=numbers.index(odd_numbers[odd_idx], i)
            swaps+=odd_idx_swap-i
            numbers.insert(i, numbers.pop(odd_idx_swap))
        odd_idx+=1
    elif i&1==0:
        if even_numbers[even_idx]!=numbers[i]:
            even_idx_swap=numbers.index(even_numbers[even_idx], i)
            swaps+=even_idx_swap-i
            numbers.insert(i, numbers.pop(even_idx_swap))
        even_idx+=1
# print(numbers)
# print(even_numbers)
# print(odd_numbers)
print(swaps)