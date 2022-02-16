%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 03_vectors
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Initializing sample data\n');

row_vec = [ 1, 2, 3 ]
row_vec = [ 1 2 3 ]

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Semicolon operator\n');

row_vec = 0:3:12  % first:step:last
row_vec = 0:5:20  % first:step:last

row_vec = 0:5     % first:last (default step=1)
row_vec = 5:0     % first:last (default step=1) - EMPTY

row_vec = 5:-1:0  % first:step:last

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> linspace\n');

row_vec = linspace( 20, 30, 4 ) % first, last, number of point
row_vec = linspace( 1, 100 )    % first, last, (default number of point=100)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> logspace\n');

row_vec = logspace( 1, 2, 3 ) % logspace(x,y,n) from 10^x to 10^y, n - number of points
row_vec = logspace( 1, 2 )    % logspace(x,y,n) n default = 50

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Concatenate\n');

% concat
vec1 = [ 1 2 3 ]
vec2 = [ 4 5 ]
vec3 = [ vec1 vec2 ]
vec3 = [ vec1 6 7 ]

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Indeces\n');

% index
vec4 = [ 11 22 33 44 55 66 ]
vec4(1)
vec4(2)
vec4(3)
vec4([ 2 5 ])
vec4([ 2;5 ])
vec4([ 2:5 ])

vec4(2) = 202

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Misc\n');

vec5 = 1:3
vec5(5:6) = [10,20]
