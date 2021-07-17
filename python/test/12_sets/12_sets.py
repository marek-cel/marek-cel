#!/usr/bin/env python3

################################################################################

set1 = { 1, 2, 3, 4 }
set2 = { 1, 1, 1, 1 }
set3 = set( "abracadabra" )
set4 = { x for x in "abracadabra" if x not in "abc" }

print( set1 )
print( set2 )
print( set3 )
print( set4 )

set1.add( 1 )
set2.add( 1 )

print( set1 )
print( set2 )

set1.add( 2 )
set2.add( 2 )

print( set1 )
print( set2 )

################################################################################
