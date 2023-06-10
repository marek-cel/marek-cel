#include <FindNode.h>

////////////////////////////////////////////////////////////////////////////////

osg::Node* FindNode::findFirst( osg::Node *node, const char *name )
{
    if ( node )
    {
        FindNode findNode( name );
        node->accept( findNode );
        return dynamic_cast<osg::Node*>( findNode.getFirst().get() );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::findNodes( osg::Node *node, const char *name )
{
    if ( node )
    {
        FindNode findNode( name, true );
        node->accept( findNode );
        return findNode.getNodes();
    }

    return Nodes();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode() :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    _findAll ( false )
{
    _name = "";
    _nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode( const char *name, bool findAll ) :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    _findAll ( findAll )
{
    _name = name;
    _nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

void FindNode::apply( osg::Node &searchNode )
{
    if ( _name == searchNode.getName() || _name.length() == 0 )
    {
        osg::ref_ptr<osg::Node> tempNode = &searchNode;

        _nodes.push_back( tempNode.get() );

        if ( _findAll ) traverse( searchNode );
    }
    else
    {
        traverse( searchNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

osg::ref_ptr<osg::Node> FindNode::getFirst()
{
    if ( _nodes.empty() )
    {
        return 0;
    }
    else
    {
        return _nodes[ 0 ];
    }
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::getNodes()
{
    return _nodes;
}
