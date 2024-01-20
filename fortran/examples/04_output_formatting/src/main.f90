program myprog
    
    implicit none ! force to declear all variables

    character(len=5) :: i_char

    print *, "A number ", 10
    print "(3i5)", 7, 14, 212
    print "(3i5)", 212, 14, 7
    print "(i5)", 7, 14, 212

    print "(2f8.2)", 3.1415, 1.234

    print "(/, 2a8)", "Name", "Age"

    print "(e10.3)", 123.456789

    print "(a15,i2)", "I am ", 39

    write (i_char, "(i2)") 10
    print "(a,a)", "A number ", adjustl(i_char)

end program myprog