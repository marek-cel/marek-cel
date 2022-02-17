%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 16_if_else
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear

a = input('Enter ''a'' parameter ');
b = input('Enter ''b'' parameter ');
c = input('Enter ''c'' parameter ');

if a ~= 0
  d = b^2 - 4*a*c
  
  if d >= 0
    fprintf('Real roots:\n');
    x1 = -b + sqrt(d) / ( 2.0 * a )
    x2 = -b - sqrt(d) / ( 2.0 * a )
  else  
    fprintf('Complex roots:\n');
    x1 = -b + sqrt(d) / ( 2.0 * a )
    x2 = -b - sqrt(d) / ( 2.0 * a )
  end
else
  fprintf('Division by zero\n');
end

disp('press any key to continue');
pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear

balance = input('Enter account balance ');

if balance < 1000
  fprintf('Interest rate= %f\n', 0.0);
elseif balance >= 1000 & balance < 10000
  fprintf('Interest rate= %f\n', 0.1);
else
  fprintf('Interest rate= %f\n', 0.2);
endif
