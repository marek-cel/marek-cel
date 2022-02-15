################################################################################
# 12_fprintf
################################################################################

fprintf( "%f \n", pi )
fprintf( "%d \n", 101 )
fprintf( "%c \n", 'c' )
fprintf( "%s \n", 'string' )
fprintf( "%c \n", 'xyz' )

pause

fprintf("\n")
fprintf( "a= %d km\n", 101 )
fprintf( "a= %10d km\n", 101 )
fprintf( "a= %-10d km\n", 101 )

pause

fprintf("\n")
fprintf( "pi= %f \n", pi )
fprintf( "pi= %10f \n", pi )
fprintf( "pi= %.2f \n", pi )
fprintf( "pi= %5.2f \n", pi )

pause

fprintf("\n")
fprintf( '\t '' \\ '' \\ \n', pi )
