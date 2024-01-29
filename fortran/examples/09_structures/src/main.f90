program myprog
    
    implicit none ! force to declear all variables

    type Customer
        character(20) :: name
        integer :: age
    end type Customer

    type(Customer), dimension(3) :: customers
    integer :: n

    type(Customer) :: c1
    c1%name = "John"
    c1%age = 30
    customers(1) = c1

    customers(2)%name = "Mary"
    customers(2)%age = 20

    customers(3) = Customer("Peter", 40)

    do n = 1, 3
        print *, customers(n)%name, customers(n)%age
    end do

    stop
end program myprog