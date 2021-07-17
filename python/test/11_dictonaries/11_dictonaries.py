#!/usr/bin/env python3

################################################################################

dict1 = {
    "Jack"  : 1001,
    "Sape"  : 2002,
    "Guido" : 3003
}

dict2 = dict( [ ("a", 1), ("b", 2) ] )

dict3 = { x : x*x for x in range(1,4) }

dict4 = dict( enumerate( [ "tic", "tac", "toe" ] ) )

print( dict1 )
print( dict2 )
print( dict3 )
print( dict4 )

print( dict1[ "Guido" ] )

print( dict1.get( "Jack" ) )
print( dict1.get( "Marek" ) )
print( dict1.get( "Marek", 0 ) )

print( dict1.keys() )
print( dict1.values() )
print( dict1.items() )

dict1[ "Marek" ] = 4004
print( dict1.get( "Marek" ) )

del dict1[ "Guido" ]

for key in dict1 :
    print( key, ":", dict1[ key ] )

for k,v in dict1.items() :
    print( k, ":", v )

if "Jack" in dict1 :
    print( "Jack present in dic1" )
else:
    print("Jack NOT present in dic1")

################################################################################
