package pl.marekcel.dev.cel.patterns.java.strategy;

import java.util.*;

public class Main
{
    public static void main( String[] args )
    {
        Context context = new Context();
        
        Strategy strategyMin = new StrategyMin();
        Strategy strategyMax = new StrategyMax();
        
        context.setStrategy( strategyMin );
        context.doSomething();
        
        context.setStrategy( strategyMax );
        context.doSomething();
    }
}
