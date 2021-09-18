package pl.marekcel.dev.cel.java.solid.LiskovSubstitution;

public class Rectangle implements Shape
{
    private boolean mVisible = true;
    private Point mUpperLeft;
    
    private int mWidth  = 0;
    private int mLenght = 0;

    public void moveTo( Point pnt )
    {
        mUpperLeft = pnt;
    }
    
    public void show()
    {
        mVisible = true;
    }
    
    public void hide()
    {
        mVisible = false;
    }
    
    public void setWidth( int w )
    {
        mWidth = w;
    }
    
    public void setLenght( int l )
    {
        mLenght = l;
    }
    
    public int getArea()
    {
        return mWidth * mLenght;
    }
}
