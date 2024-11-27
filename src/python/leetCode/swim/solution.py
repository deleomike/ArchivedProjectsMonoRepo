import numpy
from numpy import inf
from typing import *


class Solution:

    def __init__(self, verbose=False):
        self.verbose = verbose

    def isContinuous(self, indices, size):
        for idx in range(len(indices) - 1):
            if indices[idx] + size == indices[idx + 1]\
                    or indices[idx] - size == indices[idx + 1]\
                    or indices[idx] + 1 == indices[idx + 1]\
                    or indices[idx] - 1 == indices[idx + 1]:
                pass
            else:
                return False
        return True

    def swimInWater(self, grid: List[List[int]]) -> int:
        npGrid = numpy.array(grid)
        size = len(grid) - 1
        indices = numpy.reshape(numpy.arange(len(grid)**2), (size + 1, size + 1))

        _max = numpy.max(npGrid)

        if npGrid[size, size] == _max or npGrid[0, 0] == _max:
            return _max
        # print(numpy.max(npGrid))
        # print(npGrid)
        for t in range(_max):
            mask = npGrid <= t
            # print("--")
            # print(mask)
            floodedRows = numpy.sum(mask,axis=1).tolist()
            if mask[size, size] and mask[0, 0]:
                if 0 not in floodedRows:
                    chosenIndices = indices[mask]
                    if self.isContinuous(chosenIndices, size+1):
                        print(chosenIndices)
                        print(npGrid[mask])
                        print(mask)
                        return t
            # print("--")
        return _max




if __name__=="__main__":

    sol = Solution(verbose=False)

    print(sol.swimInWater([[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]))
    print(sol.swimInWater([[0,2],[1,3]]))