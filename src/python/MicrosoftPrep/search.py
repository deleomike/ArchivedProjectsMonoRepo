from sorting import MergeSort as sort

def BinarySearch(arr, num, leftIndex, rightIndex):
    """

    :param arr: Ordered list
    :param num:
    :return:
    """

    if rightIndex >= 1:

        mid = int((leftIndex + rightIndex) / 2)

        # Base case
        if arr[mid] == num:
            # found the number
            return mid

        elif arr[mid] < num:
            # Number is in right side
            return BinarySearch(arr, num, mid + 1, rightIndex)

        else:
            # Number is in left side
            return BinarySearch(arr, num, leftIndex, mid - 1)

    else:
        # number is not in array
        return -1


if __name__=="__main__":

    arr = [32, 321, 32, 1, 4, 6, 7, 3, 7, 9]

    print(arr)

    sorted = sort(arr)

    print(sorted)

    print("Finding: 9")

    print(BinarySearch(sorted, 9, 0, len(sorted) - 1))