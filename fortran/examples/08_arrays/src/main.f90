program myprog
    
    implicit none ! force to declear all variables

    real, dimension(3)   :: tab1
    real, dimension(4:6) :: tab2
    real, dimension(1:3) :: tab3 = [1.0, 2.0, 3.0]
    real, dimension(1:3) :: tab4 = (/ 10.0, 20.0, 30.0 /)

    real, dimension(1:2, 1:3) :: tab_2D

    integer, dimension(:), allocatable :: tab_alloc

    integer, dimension(2) :: tab_shape

    integer :: tab_size = 0

    integer, dimension(1:9) :: tab_1x9 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
    integer, dimension(1:3, 1:3) :: tab_3x3

    integer, dimension(1:3) :: a1 = [1, 1, 1]
    integer, dimension(1:3) :: a2 = [1, 2, 3]
    integer, dimension(1:6) :: a3 = [1, 2, -1, 0, 5, -3]
    integer, dimension(1:6) :: a4

    integer :: n, m

    ! accessing array elements by index
    tab1(1) = 1.0
    tab1(2) = 2.0
    tab1(3) = 3.0
    write (*,*) "tab1:"
    write (*,*) tab1
    write (*,*) "Press ENTER to continue"
    read (*,*)

    tab2(4) = 4.0
    tab2(5) = 5.0
    tab2(6) = 6.0
    write (*,*) "tab2:"
    write (*,*) tab2
    write (*,*) "Press ENTER to continue"
    read (*,*)

    write (*,*) "tab3:"
    write (*,*) tab3
    write (*,*) "Press ENTER to continue"
    read (*,*)
    
    write (*,*) "tab3 printed by loop:"
    do n = 1, 3
        write (*,*) tab3(n)
    end do
    write (*,*) "Press ENTER to continue"
    read (*,*)

    write (*,*) "tab4:"
    write (*,*) tab4
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! 2D array
    do n = 1, 2
        do m = 1, 3
            tab_2D(n,m) = n * m
        end do
    end do
    write (*,*) "tab_2D:"
    write (*,*) tab_2D(1,:)
    write (*,*) tab_2D(2,:)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    write (*,*) "Array properties"
    tab_shape = shape(tab_2D)
    write (*,*) "rank(tab_2D) ", rank(tab_2D)
    write (*,*) "size(tab_2D) ", size(tab_2D)
    write (*,*) "shape(tab_2D) ", shape(tab_2D)
    write (*,*) "tab_shape ", tab_shape
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! dynamically allocated array
    write (*,*) "Dynamic allocation"
    write (*,*) "Enter array size"
    read (*,*) tab_size
    ! allocate table
    allocate(tab_alloc(tab_size))
    do n = 1, tab_size
        tab_alloc(n) = n
    end do
    write (*,*) tab_alloc
    ! deallocate table
    deallocate(tab_alloc)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! Array sections
    write (*,*) "Array sections"
    write (*,*) "tab_1x9(3 : 6) ", tab_1x9(3 : 6)
    write (*,*) "tab_1x9(3 : 6 : 2) ", tab_1x9(3 : 6 : 2)
    write (*,*) "tab_1x9(: 6 : 2) ", tab_1x9(: 6 : 2)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! Reshape the ARRAY from 1x9 t0 3x3
    write (*,*) "Reshaping arrays"
    tab_3x3 = reshape(tab_1x9, [3, 3])
    write (*,*) "tab_1x9:"
    write (*,*) tab_1x9
    write (*,*) "tab_3x3:"
    do n = 1, 3
        write (*,*) tab_3x3(n,:)
    end do
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! math operations
    write (*,*) "Arrays math operations"
    write (*,*) "tab1 = ", tab1
    write (*,*) "tab2 = ", tab2
    write (*,*) "(tab1 + 3.0) = ", (tab1 + 3.0)
    write (*,*) "(tab1 * 2.0) = ", (tab1 * 2.0)
    write (*,*) "(tab1 + tab2) = ", (tab1 + tab2)
    write (*,*) "(tab1 * tab2) = ", (tab1 * tab2)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! comparing values of 2 arrays
    write (*,*) "Comparing values of 2 arrays"
    write (*,*) "all(a2==a3, 1) "   , all(a1==a2, 1)    ! are all equal
    write (*,*) "any(a2==a3, 1) "   , any(a1==a2, 1)    ! are any equal
    write (*,*) "count(a2==a3, 1) " , count(a1==a2, 1)  ! how many are equal
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! Get min and max value
    write (*,*) "Min and Max values of array elements"
    write (*,*) "maxval(a3) ", maxval(a3)
    write (*,*) "minval(a3) ", minval(a3)
    write (*,*) "Press ENTER to continue"
    read (*,*)
    
    ! Math operations using all array elements
    write (*,*) "Math operations using all array elements"
    write (*,*) "product(a1) ", product(a1)
    write (*,*) "sum(a1) ", sum(a1)
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! Arrays masks
    write (*,*) "Arrays masks"
    write (*,*) "a3 = ", a3
    where ( a3 < 0 )
        a3 = 0
    end where
    write (*,*) "a3 = ", a3
    write (*,*) "Press ENTER to continue"
    read (*,*)

    ! forall
    write (*,*) "forall"
    write (*,*) "a3 = ", a3
    forall (n = 1:6, a3(n) > 2.0)
        a3(n) = 2.0
    end forall
    write (*,*) "a3 = ", a3
    write (*,*) "Press ENTER to continue"
    read (*,*)

    stop
end program myprog