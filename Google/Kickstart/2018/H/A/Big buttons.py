def analyze(n, forbidden_patterns):
    forbidden_patterns = sorted(forbidden_patterns, key=lambda x: len(x))
    eliminate_redundant(forbidden_patterns)

    count = 0
    for p in forbidden_patterns:
        count += (2 ** (n - len(p)))
    return max((2 ** n) - count, 0)


def eliminate_redundant(patterns):
    eliminate = {}
    p_len = len(patterns)
    for i in range(p_len):
        for j in range(i + 1, p_len):
            if len(patterns[i]) >= len(patterns[j]):
                continue
            if patterns[j].startswith(patterns[i]):
                eliminate[patterns[j]] = 1

    for item in eliminate:
        patterns.remove(item)


if __name__ == '__main__':
    # patterns = [
    #     # 'BRBRBBBRBRRRBBB',
    #     # 'BRBRBRRRBRRRBRB',
    #     # 'BBBRBBBRBRRRBBB',
    #     # 'BRBRBRRRBRRRB',
    #     # 'BRBRBBBRBBBRB'
    #
    #     # 'R',
    #     # 'RB',
    #     # 'BRR',
    #     # 'RBRR',
    #     # 'BRBR'
    # ]

    t = int(raw_input())
    for i in range(1, t + 1):
        n, p = list(map(lambda x: int(x), raw_input().strip().split()))
        patterns = []
        for j in range(p):
            patterns.append(raw_input().strip())
        print 'Case #' + str(i) + ':', analyze(n, patterns)
