package pl.marekcel.dev.cel.patterns.java.strategy;

public class StrategyMax
    implements Strategy
{
    @Override
    public void execute( int [] data )
    {
        int max = data[0];
        for ( int i = 0; i < data.length; i++ )
        {
            if ( data[i] > max )
                max = data[i];
        }
        
        System.out.println( max );
    }
}
