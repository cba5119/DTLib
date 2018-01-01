#include <iostream>
#include "Exception.h"
#include "Object.h"
#include "SmartPointer.h"
#include "staticlist.h"
#include "dynamiclist.h"
#include "staticarray.h"
#include "dynamicarray.h"
#include "linklist.h"
#include "stdio.h"
#include "windows.h"
#include "staticlinklist.h"
#include "sharedpointer.h"
#include "circlelist.h"
#include "duallinklist.h"
#include "LinuxList.h"
#include "dualcirclelist.h"
#include "StaticStack.h"
#include "dtstring.h"
#include "cstdlib"
#include "string.h"

using namespace std;
using namespace DTLib;

class Test : public Object{
public:
    Test(int v = 0) {
        //throw 0;
        // cout<<"Test()"<<endl;
        value = v;
    }
    ~Test() {
       //cout<<"~Test()"<<endl;
    }
    bool operator == (const Test& t) {
        return this->value == t.value;
    }

    int value;
};


void StaticLinkListTest() {
    StaticLinkList<int, 2> staticList;
    staticList.insert(0,1);
    staticList.insert(0,1);

    cout<<"begin"<<endl;

    staticList.remove(0);
    cout<<"end"<<endl;
    //staticList.insert(0,1);

    cout<<staticList.length()<<endl;

}

void josephus(int n, int s, int m) {//s是起始报数 m是报数要死得人
    {
        CircleList<int> cl;
        for (int i = 0; i < n; i++) {
            cl.insert(i);
        }

        for (cl.move(s-1, m-1); !cl.end(); cl.next()) {
           cout<<cl.current()<<" "<<cl.length()<<endl;
           cl.remove(cl.find(cl.current()));
        }
    }
    {
        CircleList<int> cl;
        for (int i = 0; i < n; i++) {
            cl.insert(i);
        }
        cl.move(s-1, m-1);
        while(cl.length() > 0) {
           cl.next();//开始报数
           cout<<cl.current()<<" "<<cl.length()<<endl;
           cl.remove(cl.find(cl.current()));
        }
    }
}

void DualLinkListTest() {
    DualLinkList<Test> list;

    Test t1(1), t2(2), t3(3);

    list.insert(0, t1);
    list.insert(0, t2);
    list.insert(0, t3);

    list.remove(2);

    for (list.move(0); !list.end(); list.next()) {
        cout<<list.current().value<<endl;
    }

    for (list.move(1); !list.end(); list.pre()) {
        cout<<list.current().value<<endl;
    }
}

class Teacher {
    int b;
};

struct Student :public Teacher {
    list_head node;
    int x;
    int y;

    char z;
};

void linuxListTest() {
    list_head head;
    INIT_LIST_HEAD(&head);

    Student s1;
    s1.z = '1';
    Student s2;
    s2.z = '2';
    Student s3;
    s3.z = '3';

    list_add(&s1.node, &head);
    list_add(&s2.node, &head);
    list_add(&s3.node, &head);

    list_head* cur;

    list_for_each(cur, &head) {
        printf("%c\n", container_of(cur, Student, node)->z);
    }
}


void DualCircleListTest() {
    DualCircleList<int> list;

    for (int i = 0; i < 5; i++) {
        list.insert(0, i);
        list.insert(0, 5);
    }

    for (int i = 0; i < list.length(); i++) {
        cout<<list.get(i)<<endl;
    }

    list.move(list.length() - 1);

    while(list.find(5) != -1) {
        if (list.current() == 5) {
            cout<<list.current()<<endl;
            list.remove(list.find(list.current()));
        }
        else {
            list.next();
        }
    }

    int i = 0;
    for (list.move(list.length()-1); !list.end() && i < list.length(); list.pre()) {
        i++;
        cout<<list.current()<<endl;
    }
}

void StaticStackTest()
{
     StaticStack<int, 1> s;
     s.push(1);
     s.push(2);
}

int* make_pmt(const char* p)
{
    int len = strlen(p);
    int* ret = static_cast<int*>(malloc(sizeof(int)*len));

    if (ret != NULL)
    {
        int ll = 0;
        ret[0] = 0;
        for (int i = 1; i < len; i++)
        {
            while(ll > 0 && p[ll] != p[i])
            {
                ll = ret[ll];
            }
            if (p[ll] == p[i])
            {
                ll++;
            }
            ret[i] = ll;

        }
    }
    return ret;
}

int kmp(const char* s, const char* p)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int* pmt = make_pmt(p);
    if (pmt != NULL && 0 < pl && pl <= sl)
    {
        for (int i = 0, j = 0; i < sl; i++)
        {
            while(j > 0 && s[i] != p[j])
            {
                j = pmt[j];
            }

            if (s[i] == p[j])
            {
                j++;
            }

            if (j == pl)
            {
                ret = i + 1 - pl;
                break;
            }
        }
    }
    free(pmt);
    return ret;
}

void kmpTest()
{
    char* str = "ababax";
    int* pmt = make_pmt(str);
    for (int i = 0; i < strlen(str); i++)
    {
        //cout<<pmt[i]<<" ";
    }

    cout<<endl;

    cout<<kmp("abcde", "cde")<<endl;
}


void DTStringTest()
{
    String s = "D";
    cout<<(s == "")<<endl;
    cout<<(s < "CC")<<endl;
    cout<<(s == "hehe")<<endl;

    s += "12345";
    cout<<s.str()<<endl;
    cout<<s.length()<<endl;
    cout<<(s == "D12345")<<endl;

    String strArr[] = {"E", "F", "A", "C", "B"};

    String m = strArr[0];

    for (int i = 0; i < sizeof(strArr)/sizeof(strArr[0]); i++) {
        if (m > strArr[i]) {
            m = strArr[i];
        }
    }
    cout<<"min = "<<m.str()<<endl;

    String str = "D.T.";
    str.insert(4, "SoftWare");
    cout<<"len = "<<str.length()<<endl;
    for (int i = 0; i < str.length(); i++)
    {
        cout<<str[i]<<" ";
    }
    cout<<endl;

    cout<<str.startWith("123")<<endl;
    cout<<str.startWith("567")<<endl;
    cout<<str.endOf("123")<<endl;
    cout<<str.endOf("567")<<endl;

    cout<<" sdasdada "<<endl;

    String hehe = "  abc   ";

    cout<<hehe.length()<<endl;
    cout<<"["<<hehe.trim().str()<<"]"<<endl;
    cout<<hehe.length()<<endl;

    cout<<hehe.startWith("abc")<<endl;
    cout<<hehe.endOf("abc")<<endl;
    cout<<hehe.trim().startWith("abc")<<endl;
    cout<<hehe.trim().endOf("abc")<<endl;
    cout<<hehe.insert(0, "hzy").startWith("hzy")<<endl;
}


int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;

    //DualCircleListTest();

    //DTStringTest();

    kmpTest();

    cout << "Hello World!" << endl;
    return 0;
}
