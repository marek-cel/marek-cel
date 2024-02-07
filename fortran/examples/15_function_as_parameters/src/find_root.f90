function find_root(x_start, x_end, fun) result(x_0)
    implicit none
    real :: x_start, x_end
    real :: x_0
    interface
        function fun(x) result(y)
            implicit none
            real :: x
            real :: y
        end function
    end interface

    ! x_0 = 0.0

    return
end function