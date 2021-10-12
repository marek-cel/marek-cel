import java.util.*;

public class CompositeElement implements Element
{
    private List<Element> mElements = new ArrayList<Element>();

    public void add( Element element )
    {
        mElements.add( element );
    }

    @Override
    public void accept ( Visitor v )
    {
        Iterator it = mElements.iterator();

        while( it.hasNext() )
        {
            ( (Element)it.next() ).accept( v );
        }
    }
}

