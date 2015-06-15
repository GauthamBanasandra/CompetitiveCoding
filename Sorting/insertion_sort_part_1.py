__author__ = 'gauth_000'


def insertion_sort(array):
    unsorted_element = array[-1]
    i = len(array) - 2
    while i >= 0 and array[i] > unsorted_element:
        array[i + 1] = array[i]
        i -= 1
        display_array(array)
    array[i + 1] = unsorted_element
    display_array(array)


def display_array(array):
    num_string = ''
    for num in array:
        num_string+=str(num)+' '
    print(num_string)

def main():
    input()
    array = [int(i) for i in input().strip().split()]
    insertion_sort(array)

if __name__ == '__main__':
    main()
