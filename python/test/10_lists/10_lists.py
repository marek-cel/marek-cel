#!/usr/bin/env python3

################################################################################

list1 = [
    "marek",
    "cel",
    1984,
    1.81,
    [ 1, 2, 3 ],
    ( 4, 5, 6 )
]

list2 = [
    "lorem",
    "ipsum"
]

################################################################################

if 1984 in list1:
    print("There is 1984 in list1")
else:
    print('There isn\'t 1984 in list1')

################################################################################

print()
print( list1 )

print()
for item in list1 :
    print( item )

################################################################################

list3 = list1 + list2 + [ 10, 20 ]

print()
print( list3 )

################################################################################

print()
print( list3[ 2 ] )
print( list3[ -2 ] )
print( list3[ 2:4 ] )

################################################################################

print()
print( list3 )

del list3[ 3 ]
print( list3 )

list3.remove( 1984 )
print( list3 )

list3.append( 2021 )
print( list3 )

list3.insert( 1, "mateusz" )
print( list3 )

list3.pop(0)
list3.pop()
print( list3 )

list3.reverse()
print( list3 )

list2.sort()
print( list2 )

list3[ 0 ] = "xxx"
print( list3 )

print( list3[4][1] )

################################################################################

nickname31 = list3
nickname32 = list3

nickname31[ 0 ] = "YYY"
print( list3 )

nickname32[ 0 ] = "ZZZ"
print( list3 )

################################################################################
