__author__ = 'gauth_000'


def get_required_class_strength(strength):
    return int(strength.split()[1])


def get_arrival_timings(timings):
    timings_list = []
    for time in timings.split():
        timings_list.append(int(time))
    return timings_list


def main():
    test_cases = int(input())
    while test_cases != 0:
        count = 0
        required_class_strength = get_required_class_strength(input())
        for arrival_time in get_arrival_timings(input()):
            if arrival_time <= 0:
                count += 1
        if count >= required_class_strength:
            print('NO')
        else:
            print('YES')


if __name__ == '__main__':
    main()
