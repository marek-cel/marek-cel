#pragma once

#include <vector>

#include "Element.h"

class CompositeElement : public Element
{
public:

    void add( Element *element )
    {
        _children.push_back( element );
    }

    void accept ( Visitor *v )
    {
        for ( auto c : _children )
        {
            c->accept( v );
        }
    }

private:

    std::vector<Element*> _children;
};

