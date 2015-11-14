__author__ = 'gauth_000'


def insertion_sort(array):
    for i in range(1, len(array)):
        v = array[i]
        j = i - 1
        while j >= 0 and array[j] > v:
            array[j + 1] = array[j]
            j -= 1
        array[j + 1] = v
        display_array(array)


def display_array(array):
    num_string = ''
    for num in array:
        num_string += str(num) + ' '
    print(num_string)


def main():
    input()
    array = [int(i) for i in input().strip().split()]
    insertion_sort(array)


if __name__ == '__main__':
    main()
