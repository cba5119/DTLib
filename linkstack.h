#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "linklist.h"
#include "stack.h"

//todo 在35课的时候实现了一个括号检测函数
namespace DTLib
{

template <typename T>
class LinkStack : public Stack
{

protected:
    LinkList<T> m_list;
public:
    void push(const T& e)
    {
        m_list.insert(0, e);
    }

    void pop()
    {
        if (m_list.length() > 0)
        {
            m_list.remove(0);
        }
        else {
           THROW_EXCEPTION(InValidOperationException, "No element in current stack...");
        }
    }

    T top() const
    {
        if (m_list.length() > 0)
        {
           return m_list.get(0);
        }
        else {
           THROW_EXCEPTION(InValidOperationException, "No element in current stack...");
        }
    }

    void clear()//和staticStack对比，这里复杂度是On
    {
        m_list.clear();
    }

    int size() const
    {
        return m_list.length();
    }

};



}



#endif // LINKSTACK_H
