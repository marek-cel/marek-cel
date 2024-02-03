program myprog
    
    implicit none ! force to declear all variables

    integer :: var1
    integer :: var2
    integer :: var3

    open(1, file = "data_new.txt", status = "new")
    write (1,*) "my new output file"
    close(1)

    open(2, file = "data_old.txt", status = "old")
    read (2,*) var1
    read (2,*) var2, var3
    close(2)

    write (*,*) var1
    write (*,*) var2
    write (*,*) var3

    open(3, file = "data_unknown.txt", status = "unknown")
    write (3,*) "my unknown output file"
    close(3)
    
    stop
end program myprog