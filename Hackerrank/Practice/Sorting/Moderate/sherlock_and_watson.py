__author__ = 'gauth_000'
# The solution is not to rotate the array at all, the answer is write a simple math function that translates the indices
# from before to after rotation.
n, k, q=list(map(int, input().strip().split()))
numbers=list(map(int, input().strip().split()))
queries=[int(input()) for i in range(q)]
print('\n'.join(map(str, [numbers[index] for index in [i-k%n if i-k%n>=0 else i-k%n+n for i in queries]])))