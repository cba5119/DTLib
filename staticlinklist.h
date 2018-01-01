#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "linklist.h"

namespace DTLib
{

template< typename T, int N >
class StaticLinkList : public LinkList<T>//内存分配是自己已经分配好的，这样效率会高一些
{
    typedef typename LinkList<T>::Node Node;

    struct SNode : public Node {//为了调用new的时候是自己这边分的内存，因为node是基类，无法修改基类代码，所以要继承
        void* operator new(unsigned int size, void* loc) {
            (void)size;
            return loc;
        }
    };

protected:
    unsigned char m_space[sizeof(Node) * N];
    int m_used[N];

    Node* create() {//由于staticlinklist和一般linklist只有内存分配的不同，所以重载create和destroy就可以了
        SNode* ret = NULL;
        for (int i = 0; i < N; i++) {
            if (!m_used[i]) {
                ret = reinterpret_cast<SNode*>(m_space)+i;
                ret = new(ret)SNode();//注意这里的用法，手动分配内存
                m_used[i] = 1;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn) {
        SNode* tmp = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);
        for (int i = 0; i < N; i++) {
            if (psn == (tmp + i)) {
                m_used[i] = 0;
                tmp->~SNode();
                break;
            }
        }
    }
public:
    StaticLinkList() {
        for (int i = 0; i < N; i++) {
            m_used[i] = 0;
        }
    }

    ~StaticLinkList() {
        this->clear();//析构函数中不会多态，嵌套调用也不会发生多态，所以父类不会调用子类的destroy，所以在自己析构这里调用clear来释放
        //如果不这么做会出潜在的问题，比如如果insert两个元素，然后remove第一个，就会出调用pure virtual function call的错误，不好查
        //注意析构顺序是先调子类，所以子类释放过后list就清空了，这样不干扰父类
    }

    int capacity() {
        return N;
    }
};

}

#endif // STATICLINKLIST_H
