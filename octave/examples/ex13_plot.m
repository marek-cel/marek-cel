clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x = 0:pi/40:4*pi;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

plot(x,sin(x),'b-*')
hold on
plot(x,cos(x),'r-o')
xlabel('x')
ylabel('sin(x),cos(x)')
title('Sine and cosine functions plot')
legend('sin(x)','cos(x)')
axis([0 4*pi -1.2 1.2])
grid on
hold off

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

plotyy(x, sin(x), x, 2*cos(x))
xlabel('x')
ylabel('sin(x)')
ylabel('2*cos(x)')