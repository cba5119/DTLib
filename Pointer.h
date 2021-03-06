#ifndef POINTER_H
#define POINTER_H

#include "Object.h"

namespace DTLib
{

template < typename T >
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL)
    {
        m_pointer = p;
    }

    const T* operator-> () const//只读对象会调用这个 返回值是const那么sp管理的指针也不可以赋值了
    {
        return m_pointer;
    }

    const T& operator* () const//只读对象会调用这个 返回值是const那么sp管理的指针也不可以赋值了
    {
        return *m_pointer;
    }

    T* operator-> ()
    {
        return m_pointer;
    }

    T& operator* ()
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return (m_pointer == NULL);
    }

    T* get() const
    {
        return m_pointer;
    }
};


}


#endif // POINTER_H
