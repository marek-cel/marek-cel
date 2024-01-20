clear all

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Initializing smaple data\n');

m1 = [ 1 2 3 ; 4 5 6 ; 7 8 9 ]

m2 = [ 1 2 3 ; ...
       4 5 6 ; ...
       7 8 9 ]

pause       

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> rand\n');

m_rand = rand(3)    % creates 3x3 with random values
m_rand = rand(3,4)  % creates 3x4 (rows x cols) with random values
m_randi = randi([0 9],3,3)

display('>>> zeros\n');

m_zeros = zeros(3)
m_zeros = zeros(3,4)

display('>>> ones\n');

m_ones = ones(3)
m_ones = ones(3,4)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> Indices\n');

m2(2,3) % index_row, index_col 6
m2(2,3) = 66

m2(:,3)
m2(:,3) = 33

m1(1,:)
m1(1,:) = 11

m1(1,:) = 5:5:15
m2(:,3) = [ 10 20 30 ]'

m1(end,1)
m1(1,end)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> length\n');
length(m1) % returns largest dimension (in case of 3x4 matrix it gives 4)

display('>>> numel\n');
numel(m1)  % returns number of elements

display('>>> Size\n');
size(m1)   % return 2D vector [ rows cols ]

display('>>> Assigning elements to variables\n');
[ r c ] = size(m1)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> reshape\n');

m0 = [ 1 2 3 4 ; ...
       5 6 7 8 ; ...
       9 10 11 12 ]

m0_reshaped = reshape(m0, 1, 12 )
m0_reshaped = reshape(m0, 2, 6 )

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

m04 = [ 1 2 3 ; ...
       4 5 6 ; ...
       7 8 9 ]

display('>>> rot90\n');
m_rot90 = rot90(m04)

display('>>> flip\n');
m_flip = flip(m04)

display('>>> flipud\n');
m_flipud = flipud(m04)

pause

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

display('>>> vector as index\n');
m05 = randi([0 10], 5, 5)
m05([1:2:5],:)
