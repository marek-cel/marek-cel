clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Initializing\n');

colvec = [1; 3; 5]

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Transposing\n');

rowvec1 = 1:2:5
colvec1 = transpose(rowvec1)

rowvec2 = 2:2:6
colvec2 = rowvec2'  % transpose

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Indices\n');

colvec3 = [1; 3; 5]
colvec3(2) = 300
