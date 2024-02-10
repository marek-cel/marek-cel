#!/usr/bin/env python3

################################################################################

import pickle, shelve

################################################################################

list1 = ["xxx", "yyy", "zzz"]
list2 = ["aaa", "bbb", "ccc"]

dict1 = {
  "key1" : "val1",
  "key2" : "val2"
}

print(list1)
print(list2)
print(dict1)

################################################################################

file1 = open("output1.dat", "wb")

pickle.dump(list1, file1)
pickle.dump(list2, file1)
pickle.dump(dict1, file1)

file1.close()

################################################################################

file2 = open("output1.dat", "rb")

list21 = pickle.load(file2)
list22 = pickle.load(file2)

dict21 = pickle.load(file2)

file2.close()

print()
print(list21)
print(list22)
print(dict21)

################################################################################

shelve1 = shelve.open("shelve.dat")

shelve1["list1"] = list1
shelve1["list2"] = list2
shelve1["dict1"] = dict1

shelve1.close()

################################################################################

shelve2 = shelve.open("shelve.dat")

list31 = shelve2["list1"]
list32 = shelve2["list2"]
dict31 = shelve2["dict1"]

shelve2.close()

print()
print(list31)
print(list32)
print(dict31)

################################################################################
