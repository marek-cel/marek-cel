clear all

pkg load symbolic

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

syms f x y

f = sin(x)^2 + cos(y)^2

diff(f)
diff(f, y) % differential against y

diff(f, 2)
diff(diff(f))

f = 2*x

int(f)
int(f, 0 , 2) % determining integral
