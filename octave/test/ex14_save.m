clear all

x = -4:0.1:4;
y = x.^2;

plot(x,y)

d = [ x' y' ];

save -ascii ex14_data.txt d
