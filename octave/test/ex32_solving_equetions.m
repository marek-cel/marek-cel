clear all

pkg load symbolic

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Solving linear equation...')

syms f x

f = 2*x - 2
solve(f)

f = 2*x - 2 == 0
solve(f)

f = 2*x  == 2
solve(f)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Solving quadratic equation...')

f = x^2 - 2
solve(f)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Solving polynominal equation...')

f = 2*x^2 + 3*x - 1
solve(f)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('Solving system of equations...')

syms f1 f1 x y

f1 = x + 2*y == 7
f2 = 2*x - y == 1

[x y] = solve( f1, f2 )

