package pl.marekcel.dev.cel.patterns.java.strategy;

public class StrategyMin
    implements Strategy
{
    @Override
    public void execute( int [] data )
    {
        int min = data[0];
        for ( int i = 0; i < data.length; i++ )
        {
            if ( data[i] < min )
                min = data[i];
        }
        
        System.out.println( min );
    }
}
