program myprog
    
    implicit none ! force to declear all variables

    real, parameter :: PI = 3.1415 ! parameter is a constant
    real :: r_num1 = 0.0, r_num2 = 0.0
    real (kind=8) :: r8_num = 1.1111111111111111
    double precision :: dbl_num = 1.1111111111111111
    integer :: i_num1 = 0, i_num2 = 0
    logical :: flag = .true.
    character (len = 10) :: text
    complex :: c_num = (2.0 + 3.0)

    write (*,*) "Biggest Real ", huge(r_num1)
    write (*,*) "Smallest Real ", tiny(r_num1)

    write (*,*) "Int ", kind(i_num1), " bytes"
    write (*,*) "Real ", kind(r_num1), " bytes"
    write (*,*) "Real8 ", kind(r8_num), " bytes"
    write (*,*) "Double ", kind(dbl_num), " bytes"
    write (*,*) "Bool ", kind(flag), " bytes"

    stop
end program myprog