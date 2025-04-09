#ifndef FOOBAR_H
#define FOOBAR_H

#if defined(_MSC_VER)
#   if defined(FOOBAR_DLL_EXPORTS)
#       define FOOBAR_DLL_SPEC __declspec(dllexport)
#   else
#       define FOOBAR_DLL_SPEC __declspec(dllimport)
#   endif
#else
#   define FOOBAR_DLL_SPEC
#endif

#if defined(__cplusplus)
#   define FOOBARAPI FOOBAR_DLL_SPEC
#endif

#if !defined(FOOBARAPI)
#   define FOOBARAPI
#endif


class FOOBARAPI FooBar
{
public:

    FooBar();
    ~FooBar();

    void greet();
};


extern "C" {

    FOOBARAPI FooBar* FooBar_new()
    {
        return new FooBar();
    }

    FOOBARAPI void FooBar_greet(FooBar* foo)
    {
        foo->greet();
    }

    FOOBARAPI void FooBar_delete(FooBar* foo)
    {
        delete foo;
    }

}

#endif // FOOBAR_H
