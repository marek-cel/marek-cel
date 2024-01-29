program myprog
    implicit none ! force to declear all variables

    ! character*20 :: name ! old style
    character(20) :: name

    write (*,*) "What's your name?"
    read (*,*) name
    write (*,*) "Hello ", name
    
    stop
end program myprog