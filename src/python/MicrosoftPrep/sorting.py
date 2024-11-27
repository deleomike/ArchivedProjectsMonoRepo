import math


def MergeSort(arr):

    """
    :param arr: unsorted array
    :return:
    """

    if len(arr) > 1:

        # Get middle index
        mid = math.floor(len(arr) / 2)

        # Sort left array
        leftSide = arr[:mid]

        # Sort the right array
        rightSide = arr[mid:]

        leftSide = MergeSort(leftSide)

        rightSide = MergeSort(rightSide)

        return merge(leftSide, rightSide)

        # print("{} {}".format(leftSide, rightSide))

    else:
        # Base case of length 1 or 0 array
        return arr


def merge(leftArray, rightArray):

    merged = []

    # Initialize the two index pointers
    leftIndex = 0
    rightIndex = 0

    while leftIndex < len(leftArray) and rightIndex < len(rightArray):

        # Check if left array number is less than right array number
        if leftArray[leftIndex] <= rightArray[rightIndex]:
            # Left array has the smaller number

            merged.append(leftArray[leftIndex])

            # increment index
            leftIndex += 1

        else:
            # Right array has the smaller number

            merged.append(rightArray[rightIndex])

            rightIndex += 1

    # make sure there are no numbers left

    while leftIndex < len(leftArray):
        merged.append(leftArray[leftIndex])
        leftIndex += 1

    while rightIndex < len(rightArray):
        merged.append(rightArray[rightIndex])
        rightIndex += 1

    return merged




if __name__=="__main__":

    tmp = [3, 2, 9, 4, 2, 1]

    print(tmp)

    res = MergeSort(tmp)

    print(res)