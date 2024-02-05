program myprog
    implicit none

    interface 
        subroutine roots(a, b, c, x1, x2)
            implicit none
            real, intent(in)  :: a, b, c
            real, intent(out) :: x1, x2
        end subroutine
    end interface

    real :: a, b, c, x1, x2

    real :: aa = 2.0
    real :: bb = 3.0

    integer :: n

    write (*,*) "Computing roots of a quadratic equation in the following form:"
    write (*,*) "a*x^2 + b*x + c = 0"
    write (*,*) "Enter values of a, b, c parameters"
    read (*,*) a, b, c
    call roots(a, b, c, x1, x2)
    write (*,*) "x1= ", x1
    write (*,*) "x2= ", x2
    write (*,*) "Press ENTER to continue"
    read (*,*)

    call foo()
    write (*,*) "Outside foo ", aa, bb
    write (*,*) "Press ENTER to continue"
    read (*,*)

    write (*,*) "Calling bar 5 times"
    do n = 1, 5
        call bar()
    end do
    write (*,*) "Press ENTER to continue"
    read (*,*)

    stop

    contains
        subroutine foo()
            implicit none
            real :: bb = 10.0
            real :: cc = 20.0

            aa = bb
            bb = cc

            write (*,*) "Inside foo ", aa, bb

            return
        end subroutine

        subroutine bar()
            implicit none
            integer, save :: call_counter = 0

            call_counter = call_counter + 1
            write (*,*) "bar called ", call_counter, " times"

            return
        end subroutine
end program