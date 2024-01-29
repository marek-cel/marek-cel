program myprog
    
    implicit none ! force to declear all variables

    real :: float_num = 1.1111111111111111111
    real :: float_num2 = 1.1111111111111111111
    real (kind=8) :: float8_num = 1.1111111111111111111
    real (kind=8) :: float8_num2 = 1.1111111111111111111
    double precision :: dbl_num = 1.1111111111111111111d+0
    double precision :: dbl_num2 = 1.1111111111111111111d+0

    print "(a8,2f8.2)", "3 + 2 = ", (3.0 + 2.0)
    print "(a8,2f8.2)", "3 - 2 = ", (3.0 - 2.0)
    print "(a8,2f8.2)", "3 * 2 = ", (3.0 * 2.0)
    print "(a8,2f8.2)", "3 / 2 = ", (3.0 / 2.0)
    print "(a8,2f8.2)", "3 % 2 = ", mod(3.0, 2.0)
    print "(a8,2f8.2)", "3 ^ 2 = ", (3.0 ** 2.0)
    
    print *, ""

    print "(f17.15)", (float_num + float_num2)
    print "(f17.15)", (float8_num + float8_num2)
    print "(f17.15)", (dbl_num + dbl_num2)

    stop
end program myprog