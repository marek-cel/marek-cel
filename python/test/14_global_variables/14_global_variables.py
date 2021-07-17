#!/usr/bin/env python3

################################################################################

def read_global():
    print( "read_global() val=", val )

################################################################################

def shadow_global():
    val = 2
    print("shadow_global() val=", val)

################################################################################

def change_global():
    global val
    val = 4
    print("change_global() val=", val)

################################################################################

val = 7

read_global()
print( "val=", val )

shadow_global()
print( "val=", val )

change_global()
print( "val=", val )


################################################################################
