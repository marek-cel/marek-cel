program myprog
    
    implicit none ! force to declear all variables

    integer, dimension(3) :: a1
    integer, dimension(1:3) :: a2 = [1,2,3]
    integer, dimension(1:3) :: a3 = (/ 1, 2, 9 /)
    integer, dimension(2,5) :: a4
    integer, dimension(:), allocatable :: a5
    integer, dimension(1:9) :: a6 = (/ 1,2,3,4,5,6,7,8,9 /)
    integer, dimension(1:3,1:3) :: a7
    integer :: num_vals = 0
    integer :: n, m

    a1(1) = 5
    print "(i1)", a1(1)
    
    print *, ""
    do n = 1, 3
        print "(i1)", a3(n)
    end do

    print *, ""
    print "(3i2)", a3(1:3)

    print *, ""
    print "(3i2)", size(a2)

    print *, ""
    do n = 1, 2
        do m = 1, 3
            a4(n,m) = n + m
        end do
        print "(3i2)", a4(n,1:3)
    end do

    print *, ""
    print "(3i2)", rank(a4)
    print "(3i2)", size(a4)
    print "(3i2)", shape(a4)

    print *, ""
    print *, "Enter array size"
    read *, num_vals
    allocate(a5(num_vals))
    do n = 1, num_vals
        a5(n) = n
    end do
    print "(100i2)", a5(1:num_vals)
    deallocate(a5)

    ! Reshape the ARRAY from 1x9 t0 3x3
    a7 = reshape(a6, (/ 3, 3 /))

    ! Check if values are equal across the 1 dimension
    print "(l1)", all(a2==a3, 1)

    ! Are any equal?
    print "(l1)", any(a2==a3, 1)

    ! How many are equal
    print "(i1)", count(a2==a3, 1)

    ! Get min and max value
    print "(i1)", maxval(a3)
    print "(i1)", minval(a3)
    
    ! Get product and sum
    print "(i3)", product(a3)
    print "(i2)", sum(a3)

end program myprog