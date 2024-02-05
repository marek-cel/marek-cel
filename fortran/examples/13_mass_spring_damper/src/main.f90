program myprog
    implicit none ! force to declear all variables

    real, parameter :: G = 9.81 ! [m/s^2] gravity acceleration

    real :: v = 0.0 ! [m/s] velocity
    real :: x = 0.0 ! [m] position
    real :: k = 0.0 ! [N/m] spring constant
    real :: c = 0.0 ! [N/m/s] damping coef
    real :: m = 0.0 ! [kg] mass
    real :: t = 0.0 ! [s] time
    real :: dt = 0.01 ! [s] time step

    real :: dx_dt = 0.0 ! [m/s] velocity
    real :: dv_dt = 0.0 ! [m/s^2] acceleration

    ! dx/dt = v
    ! dv/dt = -(x*k + v*c) / m + G

    ! write (*,*) "Enter mass"
    ! read (*,*) m

    ! write (*,*) "Enter spring constant"
    ! read (*,*) k

    ! write (*,*) "Enter dampipng coef"
    ! read (*,*) k

    m = 1.0
    k = 10.0
    c = 1.0

    open(1, file = "data.txt", status = "unknown")

    do while ( t <= 5.0 )
        dv_dt = -(x*k + v*c) / m + G
        dx_dt = v
        x = x + dt * dx_dt
        v = v + dt * dv_dt
        write (*,*) t, x, v
        write (1,*) t, x, v
        t = t + dt
    end do

    close(1)

    stop
end program myprog