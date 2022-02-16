%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 15_user_defined_functions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear

function [ output ] = myfun2(arg1, arg2)
  % myfun - file name should match function name
  output = arg1 - arg2;
end

a1 = myfun1(1, 2);
a2 = myfun2(1, 2);

fprintf('a1= %f\n', a1);
fprintf('a2= %f\n', a2);
