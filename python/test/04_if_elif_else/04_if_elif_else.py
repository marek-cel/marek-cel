#!/usr/bin/env python3

################################################################################

password = input( "Enter password " )

if password == "secret" :
    print( "Access granted" )
else :
    print( "Access denied" )

################################################################################

a1 = int( input( "Enter 1st value " ) )
a2 = int( input( "Enter 2nd value " ) )

if a1 < a2 :
    print( "a1 less than a2" )
elif a1 > a2 :
    print( "a1 greater than a2" )
else :
    print( "a1 equals a2" )

################################################################################

if False :
    print( "True" )

    print( "aaa" )

else:
    print( "False" )

    print( "bbb" )

print( "ccc" )

################################################################################
