program myprog
    implicit none ! force to declear all variables

    character(3) :: file_extension = "txt"
    character(4) :: file_name = "data"
    character(8) :: full_name
    character(80) :: buffer

    ! concatenation
    full_name = file_name // "." // file_extension
    write (*,*) full_name

    ! ASCII codes
    write (*,*) char(40)

    ! writing to buffer
    write (buffer,*) "lorem ipsum"
    write (*,*) buffer

    stop
end program myprog