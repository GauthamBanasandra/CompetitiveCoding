__author__ = 'gauth_000'


def get_sticks():
    num_of_sticks = int(input())
    sticks = input().split()
    for i in range(num_of_sticks):
        sticks[i] = int(sticks[i])
    return sticks


def main():
    sticks = get_sticks()
    while len(sticks) > 0:
        count = 0
        stick_min = min(sticks)
        for i in range(len(sticks)):
            sticks[i] = sticks[i] - stick_min
            count += 1
        print(count)

        while 0 in sticks:
            sticks.remove(0)


if __name__ == '__main__':
    main()
