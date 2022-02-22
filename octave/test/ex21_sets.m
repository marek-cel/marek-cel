clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

a = [ 9 8 5 3 7 2 ]
b = [ 1 4 2 0 6 3 ]

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% czesc wspolna
intersect(a, b)

% superpozycja
union(a, b)

% roznica zbiorow
setdiff(a, b)

% roznica symetryczna zbiorow
setxor(a, b)

ismember(a, 1)
ismember(a, 9)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

v = [ 1 1 1 2 2 3 3 4 5 6 ]

m = [ 1 1 1 2 ; 1 1 2 3 ; 2 3 4 5 ]

unique(v)
unique(m)