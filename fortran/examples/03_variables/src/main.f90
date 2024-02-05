program myprog
    
    implicit none ! force to declear all variables

    real, parameter :: PI = 3.1415 ! parameter is a constant
    real, parameter :: G = 9.81 ! parameter is a constant

    real :: r_num1 = 0.0, r_num2 = 0.1
    real :: r_num = 1.1111111111111111
    real (kind=8) :: r8_num = 1.1111111111111111d+0
    real (8) :: r8_num2 = 1.1111111111111111d+0
    double precision :: dbl_num = 1.1111111111111111d+0

    integer :: i_num1 = 0, i_num2 = 0

    logical :: flag = .true.
    
    character (len = 10) :: text
    
    complex :: c_num = (2.0 + 3.0)

    r_num1 = r_num1 + r_num2 ! 0.1
    r_num1 = r_num1 + r_num2 ! 0.2
    r_num1 = r_num1 + r_num2 ! 0.3
    r_num1 = r_num1 + r_num2 ! 0.4
    r_num1 = r_num1 + r_num2 ! 0.5
    r_num1 = r_num1 + r_num2 ! 0.6
    r_num1 = r_num1 + r_num2 ! 0.7
    r_num1 = r_num1 + r_num2 ! 0.8
    r_num1 = r_num1 + r_num2 ! 0.9
    r_num1 = r_num1 + r_num2 ! 1.0

    write (*,*) "r_num1 ", r_num1
    write (*,*) "r_num + r_num ", (r_num + r_num)
    write (*,*) "r8_num + r8_num ", (r8_num + r8_num)
    write (*,*) "r8_num2 + r8_num2 ", (r8_num2 + r8_num2)
    write (*,*) "dbl_num + dbl_num ", (dbl_num + dbl_num)

    write (*,*) "Biggest Real ", huge(r_num1)
    write (*,*) "Smallest Real ", tiny(r_num1)

    write (*,*) "Int ", kind(i_num1), " bytes"
    write (*,*) "Real ", kind(r_num1), " bytes"
    write (*,*) "Real8 ", kind(r8_num), " bytes"
    write (*,*) "Double ", kind(dbl_num), " bytes"
    write (*,*) "Bool ", kind(flag), " bytes"

    stop
end program myprog