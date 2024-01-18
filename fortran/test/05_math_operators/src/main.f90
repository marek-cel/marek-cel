program myprog
    
    implicit none ! force to declear all variables

    real :: float_num = 1.1111111111111111111
    real :: float_num2 = 1.1111111111111111111
    double precision :: dbl_num = 1.1111111111111111111d+0
    double precision :: dbl_num2 = 1.1111111111111111111d+0

    print "(a8,i1)", "5 + 4 = ", (5 + 4)
    print "(a8,i1)", "5 - 4 = ", (5 - 4)
    print "(a8,i2)", "5 * 4 = ", (5 * 4)
    print "(a8,i1)", "5 / 4 = ", (5 / 4)
    print "(a8,i1)", "5 % 4 = ", mod(5, 4)
    print "(a8,i3)", "5 ^ 4 = ", (5**4)
    
    print *, ""

    print "(f17.15)", (float_num + float_num2)
    print "(f17.15)", (dbl_num + dbl_num2)

end program myprog