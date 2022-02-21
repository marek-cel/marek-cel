clear all

x = 0 : pi/40 : 4*pi;

subplot( 2, 2, 1 );
plot( x, sin(x) );
subplot( 2, 2, 2 );
plot( x, cos(x) );
subplot( 2, 2, 3 );
plot( x, x.^2 );
subplot( 2, 2, 4 );
plot( x, log(x) );
