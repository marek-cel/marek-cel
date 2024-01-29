program myprog
    
    implicit none ! force to declear all variables

    integer :: age = 16
    integer :: n = 0, m = 0

    if ((age >= 5) .and. (age <= 6)) then
        print *, "You are in kindergarten"
    else if ((age >= 7) .and. (age <= 13)) then
        print *, "You are in middle school"
    else if ((age >= 14) .and. (age <= 18)) then
        print *, "You are in high school"
    else
        print *, "You are not in school"
    end if

    if (age /= 16) then
        print *, "You are not 16"
    else
        print *, "You are 16"
    end if

    select case(age)
        case(5:6)
            print *, "You are in kindergarten"
        case(7:13)
            print *, "You are in middle school"
        case(14, 15, 16, 17, 18)
            print *, "You are in high school"
        case(21)
            print *, "You are 21"
        case default
            print *, "You are not in school"
    end select

    do n = 1, 10, 2
        print "(i1)", n
    end do

    do while (m < 5)
        m = m + 1
        if (mod(m, 2) == 0) then
            print "(a4,i1,a)", "m = ", m, " is even"
        else
            print "(a4,i1,a)", "m = ", m, " is odd"
        end if
    end do

    stop
end program myprog