#ifndef CGI_FINDNODE_H
#define CGI_FINDNODE_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <osg/NodeVisitor>

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Finding node visitor class.
 */
class FindNode : public osg::NodeVisitor
{
public:

    typedef std::vector< osg::ref_ptr<osg::Node> > Nodes;

    /** */
    static osg::Node* findFirst( osg::Node *node, const char *name );

    /** */
    static Nodes findNodes( osg::Node *node, const char *name );

    /** @brief Constructor. */
    FindNode();

    /** @brief Constructor. */
    FindNode (const char *name, bool findAll = false );

    /** */
    virtual void apply( osg::Node &searchNode );

    /** @brief Returns first found node. */
    osg::ref_ptr<osg::Node> getFirst();

    /** @brief Returns list of found nodes. */
    Nodes getNodes();

private:

    bool _findAll;      ///< specifies if search should be continued after finding first matching node
    std::string _name;  ///< name of the nodes to be looking for
    Nodes _nodes;       ///< found nodes list
};

////////////////////////////////////////////////////////////////////////////////

#endif // CGI_FINDNODE_H
