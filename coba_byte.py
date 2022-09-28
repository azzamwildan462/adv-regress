import numpy as np
import sys
from struct import *
from ctypes import *

import math


array = []

n = 300
n2 = 5

# Calculate the length of array
size = int(math.log(n, 256))+1

print(n.to_bytes(2, "big").hex())
print(n.to_bytes(2, "big"))

n_byte = n.to_bytes(2, "big").hex()
for i in range(0, len(n_byte), 2):
    array.append('0x'+n_byte[i]+n_byte[i+1])

halo = bytearray(n_byte, 'utf8')
print(halo)

# n2_byte = n2.to_bytes(2, "big").hex()
# for i in range(0, len(n2_byte), 2):
#     array.append('0x'+n2_byte[i]+n2_byte[i+1])

print(array)

# arr_byte2 = []
# arr_byte2[0:] = array[2:4]

# print(arr_byte2)

new_int = int.from_bytes(halo, 'big')

print(new_int)


exit()
