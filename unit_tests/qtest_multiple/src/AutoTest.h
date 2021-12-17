#ifndef AUTOTEST_H
#define AUTOTEST_H

////////////////////////////////////////////////////////////////////////////////

#include <QList>
#include <QObject>
#include <QTest>

////////////////////////////////////////////////////////////////////////////////

namespace AutoTest
{

using TestList = QList< QObject* >;

/**
 * @brief testList
 * @return
 */
inline TestList& testList()
{
    static TestList list;
    return list;
}

/**
 * @brief findObject
 * @param object
 * @return
 */
inline bool findObject( QObject* object )
{
    TestList &list = testList();

    if ( list.contains( object ) )
    {
        return true;
    }

    foreach ( QObject* test, list )
    {
        if ( test->objectName() == object->objectName() )
        {
            return true;
        }
    }

    return false;
}

/**
 * @brief addTest
 * @param object
 */
inline void addTest( QObject* object )
{
    TestList &list = testList();

    if ( !findObject( object ) )
    {
        list.append( object );
    }
}

/**
 * @brief run
 * @param argc
 * @param argv
 * @return
 */
inline int run( int argc, char *argv[] )
{
    int result = 0;

    foreach ( QObject* test, testList() )
    {
        result += QTest::qExec( test, argc, argv );
    }

    return result;
}

} // namespace AutoTest

////////////////////////////////////////////////////////////////////////////////

template <class T>
class Test
{
public:

    QSharedPointer<T> child;

    Test( const QString& name )
        : child( new T )
    {
        child->setObjectName( name );
        AutoTest::addTest( child.data() );
    }
};

////////////////////////////////////////////////////////////////////////////////

#define DECLARE_TEST(className) static Test<className> t(#className);

#define TEST_MAIN \
    int main( int argc, char *argv[] ) \
{ \
    return AutoTest::run( argc, argv ); \
}

////////////////////////////////////////////////////////////////////////////////

#endif // AUTOTEST_H
