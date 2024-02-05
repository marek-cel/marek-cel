program myprog
    implicit none
    
    write (*,*) "add1(1, 2)= ", add1(1, 2)
    write (*,*) "add2(2, 3)= ", add2(2, 3)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    stop

contains
 
    integer function add1(n1, n2)
        implicit none
        integer :: n1, n2
        add1 = n1 + n2
        return
    end function

    function add2(n1, n2) result(sum)
        implicit none
        integer :: n1, n2
        integer :: sum
        sum = n1 + n2
        return
    end function

end program