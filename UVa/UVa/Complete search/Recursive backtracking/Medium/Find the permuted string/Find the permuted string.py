import math


# RE
class KnuthsPermutation:
    def __init__(self, word, i_permutation):
        self.word = word
        self.i_permutation = i_permutation
        self.n_permutation = math.factorial(len(self.word))

    def find_permutation(self):
        return self.get_permutation(0, 1, self.n_permutation, [])

    def get_permutation(self, i_word, li_permutation, increment, permutation):
        permutation.insert(0, self.word[i_word])

        i = 0
        hi_permutation = li_permutation + increment - 1
        while self.i_permutation < li_permutation or self.i_permutation > hi_permutation:
            permutation[i], permutation[i + 1] = permutation[i + 1], permutation[i]
            i += 1
            li_permutation += increment
            hi_permutation += increment

        if i_word + 1 >= len(self.word):
            return ''.join(permutation)

        return self.get_permutation(i_word + 1, li_permutation, increment / (i_word + 2), permutation)


if __name__ == '__main__':
    for i in range(int(input())):
        print(KnuthsPermutation(input(), int(input())).find_permutation())
