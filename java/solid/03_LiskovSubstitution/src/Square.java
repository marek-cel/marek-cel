package pl.marekcel.dev.cel.java.solid.LiskovSubstitution;

public class Square implements Shape
{
    private Rectangle mRectangle = null;
    
    public Square()
    {
        mRectangle = new Rectangle();
    }

    public void moveTo( Point pnt )
    {
        mRectangle.moveTo( pnt );
    }
    
    public void show()
    {
        mRectangle.show();
    }
    
    public void hide()
    {
        mRectangle.hide();
    }
    
    public void setEdge( int a )
    {
        mRectangle.setWidth( a );
        mRectangle.setLenght( a );
    }
    
    public int getArea()
    {
        return mRectangle.getArea();
    }
}
