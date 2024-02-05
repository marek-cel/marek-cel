subroutine roots(a, b, c, x1, x2)
    implicit none

    real, intent(in) :: a, b, c
    real, intent(out) :: x1, x2
    real :: delta, sqrt_delta

    delta = b*b - 4.0*a*c

    if ( delta >= 0.0 ) then
        sqrt_delta = sqrt(delta)
        x1 = (-b + sqrt_delta) / (2.0 * a)
        x2 = (-b - sqrt_delta) / (2.0 * a)
    else
        write (*,*) "This equation has no roots"
    end if

    return
end subroutine