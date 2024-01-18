program myprog
    
    implicit none ! force to declear all variables

    real, parameter :: PI = 3.1415 ! parameter is a constant
    real :: r_num1 = 0.0, r_num2 = 0.0
    double precision :: dbl_num = 1.1111111111111111
    integer :: i_num1 = 0, i_num2 = 0
    logical :: flag = .true.
    character (len = 10) :: text
    complex :: c_num = (2.0 + 3.0)

    print *, "Biggest Real ", huge(r_num1)
    print *, "Smallest Real ", tiny(r_num1)

    print *, "Int ", kind(i_num1), " bytes"
    print *, "Real ", kind(r_num1), " bytes"
    print *, "Double ", kind(dbl_num), " bytes"
    print *, "Bool ", kind(flag), " bytes"

end program myprog