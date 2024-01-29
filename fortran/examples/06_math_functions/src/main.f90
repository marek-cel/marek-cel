program myprog
    
    implicit none ! force to declear all variables

    print "(a16,i1)", "abs(-1) = ", abs(-1)
    print "(a16,f3.1)", "sqrt(81) = ", sqrt(81.0)
    print "(a16,f7.5)", "exp(1) = ", exp(1.0)
    print "(a16,f7.5)", "log(2.71) = ", log(2.71)
    print "(a16,i1)", "int(2.71) = ", int(2.71)
    print "(a16,i1)", "nint(2.71) = ", nint(2.71)
    print "(a16,i1)", "floor(2.71) = ", floor(2.71)
    print "(a16,i1)", "ceiling(2.71) = ", ceiling(2.71)
    print "(a16,f3.1)", "max(2.7,3.4) = ", max(2.7,3.4)
    print "(a16,f3.1)", "min(2.7,3.4) = ", min(2.7,3.4)
    
    ! Trig functions use radians
    print "(a16,f3.1)", "sin(1.5708) = ", sin(1.5708)
    print "(a16,f3.1)", "cos(1.5708) = ", cos(1.5708)
    print "(a16,f3.1)", "tan(3.1415) = ", tan(3.1415)
    print "(a16,f3.1)", "asin(0) = ", asin(0.0)
    print "(a16,f3.1)", "acos(0) = ", acos(0.0)
    print "(a16,f3.1)", "atan(0) = ", atan(0.0)

    stop
end program myprog