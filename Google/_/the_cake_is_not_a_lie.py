def rotate(s, i):
    return s[i:] + s[:i]


def factors(n):
    for i in range(1, n + 1):
        if n % i == 0:
            yield i


def answer(s):
    max_pieces = 0
    for i in range(len(s)):
        cake = rotate(s, i)
        for piece_len in factors(len(cake)):
            num_pieces = 0
            piece = ''
            for i_piece in (cake[start:start + piece_len] for start in xrange(0, len(cake), piece_len)):
                if piece == '':
                    piece = i_piece
                    num_pieces += 1
                elif piece == i_piece:
                    num_pieces += 1
                else:
                    break
            else:
                max_pieces = max(max_pieces, num_pieces)
    return max_pieces


print answer('abcabcab')
