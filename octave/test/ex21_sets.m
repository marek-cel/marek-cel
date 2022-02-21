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