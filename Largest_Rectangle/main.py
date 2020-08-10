#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the largestRectangle function below.
def largestRectangle(h):
    rmax = 0    
    st = []

    pos = 1
    for i in h:
        orig_pos = pos
        while len(st):
            tst = st[-1]
            if i >= tst[0]:
                break
            else:
                local_h = tst[0]
                orig_pos = tst[1]
                local_L = pos - orig_pos
                local_max = local_L * local_h
                if local_max > rmax:
                    rmax = local_max
                st.pop()
        st.append((i, orig_pos))
        pos += 1
        
    while len(st):
        tst = st.pop()
        local_h = tst[0]
        orig_pos = tst[1]
        local_L = pos - orig_pos
        local_max = local_L * local_h        
        if local_max > rmax:
            rmax = local_max

    return rmax


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    h = list(map(int, input().rstrip().split()))

    result = largestRectangle(h)

    fptr.write(str(result) + '\n')

    fptr.close()
