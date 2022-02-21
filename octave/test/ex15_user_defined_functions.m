clear all

function [ output ] = myfun(arg1, arg2)
  % myfun - file name should match function name
  output = arg1 - arg2;
end

a1 = ex15_myfun(1, 2);
a2 = myfun(1, 2);

fprintf('a1= %f\n', a1);
fprintf('a2= %f\n', a2);
