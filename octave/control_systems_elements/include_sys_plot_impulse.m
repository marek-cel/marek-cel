legend( 'hide' );

set( gcf, 'paperposition', [0.0, 0.0, 3.0, 2.0] );

l1 = findall( gcf, 'type', 'line' );
set( l1, 'linewidth', 1.2 );

a1 = findall( gcf, 'type', 'axes' );
set( a1, 'linewidth', 0.1 );
