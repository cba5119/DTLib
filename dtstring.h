#ifndef DTSTRING_H
#define DTSTRING_H

#include "Object.h"

namespace DTLib
{

class String : public Object
{
public:
    String();
    ~String();
    String(const char* s);
    String(const String& s);
    String(char c);

    int length();
    const char* str() const;

    bool operator == (const String& s) const;
    bool operator == (const char* s) const;
    bool operator != (const String& s) const;
    bool operator != (const char* s) const;
    bool operator > (const String& s) const;
    bool operator > (const char* s) const;
    bool operator < (const String& s) const;
    bool operator < (const char* s) const;
    bool operator >= (const String& s) const;
    bool operator >= (const char* s) const;
    bool operator <= (const String& s) const;
    bool operator <= (const char* s) const;

    String operator + (const String& s) const;//注意这个是const函数 返回一个对象
    String operator + (const char* s) const;
    String& operator += (const String& s);
    String& operator += (const char* s);
    String&  operator = (const String& s);
    String&  operator = (const char* s);
    String&  operator = (char c);

    char& operator [] (int i);
    char operator [] (int i) const;
    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;
    String& insert(int i, const char* s);
    String& insert(int i, const String& s);
    String& trim();

protected:
    void init(const char* s);

    char* m_str;
    int m_length;
};


}





#endif // DTSTRING_H
