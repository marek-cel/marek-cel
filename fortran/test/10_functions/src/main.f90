program myprog
    
    implicit none ! force to declear all variables

    integer :: ans
    real :: r_ans

    ans = get_sum(1, 2)
    print "(i1)", ans

contains

    function get_sum(n1, n2) result(sum)
        implicit none
        integer :: n1, n2
        integer :: sum
        sum = n1 + n2
    end function get_sum

end program myprog