#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "duallinklist.h"
#include "linuxlist.h"


namespace DTLib
{

template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
       list_head head;
       T value;
    };

    list_head m_header;
    list_head* m_current;
    int m_length;
    int m_step;

    list_head* position(int i) const
    {
        list_head* ret = const_cast<list_head*>(&m_header);
        i = i%m_length;
        while (i--){
            ret = ret->next;
        }
        return ret;
    }

    //这里没有定义create 和 destroy函数 如果定义了会报错冲突

public:
    DualCircleList() {
        m_length = 0;
        INIT_LIST_HEAD(&m_header);
        m_step = 1;
        m_current = NULL;
    }

    virtual bool insert(int i, const T& e) {
        bool ret = (i >= 0);
        if (ret) {
            Node* node = new Node();
            if (node != NULL) {
                node->value = e;
                list_head* current = &m_header;
                i = i%(m_length+1);
                for (int n = 0; n < i; n++) {
                    current = current->next;
                }
                list_add_tail(&node->head, current->next);
                m_length++;
            }
            else {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memery...");
            }
        }
        return ret;
    }

    virtual bool insert(const T& e) {
        return insert(length(), e);
    }

    virtual bool remove(int i) {
        bool ret = (i >= 0) && (m_length > 0);
        if (ret) {
           i = i%m_length;
           list_head* toDel = position(i)->next;
           if (m_current == toDel) {
               m_current = toDel->next;
           }
           list_del(toDel);
           m_length--;
           delete list_entry(toDel, Node, head);
        }
        return ret;
    }

    virtual bool set(int i, const T& e) {
        bool ret = (i >= 0) && (m_length > 0);
        if (ret) {
            i = i%m_length;
            Node* currentNode = reinterpret_cast<Node*>(position(i)->next);
            currentNode->value = e;
        }
        return ret;
    }

    virtual bool get(int i, T& e) const {
        bool ret = (i >= 0) && (i < m_length);
        if (ret) {
            i = i%m_length;
            //用下面这种方式会有问题 可以取到head的地址，但是由于继承关系，head不一定是类的第一个成员，那么强转的地址就不是该类的地址
            //Node* currentNode = reinterpret_cast<Node*>(position(i)->next);
            Node* currentNode = list_entry(position(i)->next, Node, head);//因为这面会用到sizeof，所以计算是正确的
            e = currentNode->value;
        }
        return ret;
    }

    int find(const T& e) const {
        int ret = -1;
        list_head* m_cur;
        int i = 0;
        list_for_each(m_cur, &m_header) {
            Node* currentNode = list_entry(position(i)->next, Node, head);
            if (currentNode->value == e) {
                ret = i;
            }
            i++;
        }
        return ret;
    }

    virtual bool move(int i, int step = 1) {//移动到指定位置，设置步长
        int ret = (i >= 0 ) && (m_length > 0)&& (step > 0);
        if (ret) {
            i = i%m_length;
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    virtual bool end() {
        return (m_current == NULL) || (m_length == 0);
    }

    virtual T current() {
        if (!end()) {
            Node* currentNode = list_entry(m_current, Node, head);
            return currentNode->value;
        }
        else {
            THROW_EXCEPTION(InValidOperationException, "no value at this position...");
        }
    }

    virtual bool next() {//目的就是要跳过header，循环链表永远结束不了
        int i = 0;
        while (i < m_step && !end()) {
            if (m_current != &m_header) {
                m_current = m_current->next;
                i++;
            }
            else {
                m_current = m_current->next;
            }
        }

        if (m_current == &m_header) {
            m_current = m_current->next;;
        }
        return (i == m_step);
    }

    virtual bool pre() {
        int i = 0;
        while (i < m_step && !end()) {
            if (m_current != &m_header) {
                m_current = m_current->prev;
                i++;
            }
            else {
                m_current = m_current->prev;
            }
        }

        if (m_current == &m_header) {
            m_current = m_current->prev;;
        }
        return (i == m_step);
    }

    T get(int i) const {
        T ret;
        if (get(i, ret)) {
            return ret;
        }
        else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "index is out of range...");
        }
    }

    virtual int length() const {
        return m_length;
    }

    virtual void clear() {
       while(m_length > 0) {
            remove(0);
       }
    }

    ~DualCircleList() {
        clear();
    }

};



}


#endif // DUALCIRCLELIST_H
