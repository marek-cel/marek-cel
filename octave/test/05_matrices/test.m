################################################################################

m1 = [ 1 2 3 ; 4 5 6 ; 7 8 9 ]

m2 = [ 1 2 3 ; ...
       4 5 6 ; ...
       7 8 9 ]

################################################################################

m_rand = rand(3) # creates 3x3 with random values
m_rand = rand(3,4) # creates 3x4 (rows x cols) with random values
m_randi = randi([0 9],3,3)

m_zeros = zeros(3)
m_zeros = zeros(3,4)

m_ones = ones(3)
m_ones = ones(3,4)

################################################################################

m2(2,3) # index_row, index_col 6
m2(2,3) = 66

m2(:,3)
m2(:,3) = 33

m1(1,:)
m1(1,:) = 11

m1(1,:) = 5:5:15
m2(:,3) = [ 10 20 30 ]'

m1(end,1)
m1(1,end)

################################################################################

length(m1) # returns largest dimension (in case of 3x4 matrix it gives 4)
numel(m1)  # returns number of elements
size(m1)   # return 2D vector [ rows cols ]

[ r c ] = size(m1)

################################################################################

m0 = [ 1 2 3 4 ; ...
       5 6 7 8 ; ...
       9 10 11 12 ]

m0_reshaped = reshape(m0, 1, 12 )
m0_reshaped = reshape(m0, 2, 6 )

################################################################################

m04 = [ 1 2 3 ; ...
       4 5 6 ; ...
       7 8 9 ]

m_rot90 = rot90(m04)
m_flip = flip(m04)
m_flipud = flipud(m04)
