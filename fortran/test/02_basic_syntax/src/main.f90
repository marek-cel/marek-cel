program myprog
    implicit none ! force to declear all variables

    character*20 :: name

    print *, "What's your name?"
    read *, name
    print *, "Hello ", name
    

end program myprog