r_cg       = 0.13               # [m]
m          = 1157.0             # [kg]
g          = 9.80665            # [m/s^2]
rho        = 0.96174            # [kg/m^3]
V          = 63.79              # [m/s]
S          = 16.17              # [m^2]
c          = 1.49               # [m]
C_m        = -0.051998202222401 # [-] pitching moment coefficient
l_h        = 4.79               # [m]
S_h        = 2.0                # [m^2]
dCZ_dAoA_h = 6.33282611520831   # [1/rad]
C_Z0       = 0.09789            # [-]
dCZ_dAoA   = 5.40719            # [1/rad]
dEps_dAoA  = 0.25               # [-]

i_h = ...
( 2 * r_cg * m * g + rho * V^2 * S * c * C_m ) / ( l_h * rho * V^2 * S_h * dCZ_dAoA_h ) ...
- ( 2 * m * g - rho * V^2 * S * C_Z0 ) * ( 1 - dEps_dAoA ) / ( rho * V^2 * S * dCZ_dAoA )

i_h_deg = 180 * i_h / pi
