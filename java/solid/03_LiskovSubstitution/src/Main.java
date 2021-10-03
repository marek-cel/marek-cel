public class Main
{
    public static void main( String[] args )
    {
        Rectangle r1 = new Rectangle();
        Square s1 = new Square();
        
        r1.setWidth( 5 );
        r1.setLenght( 10 );
        
        s1.setEdge( 5 );
        
        int ar1 = r1.getArea();
        int as1 = s1.getArea();
        
        System.out.println( ar1 );
        System.out.println( as1 );
    }
}
