#include "dtstring.h"
#include "cstdlib"
#include "string.h"
#include "Exception.h"

using namespace DTLib;

#define NULL_TO_BLANK(str) (str ? str : "")

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(NULL_TO_BLANK(s));
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

void String::init(const char* s)
{
    m_str = strdup(s);
    if(m_str)
    {
        m_length = strlen(m_str);
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "no enough memeroy...");
    }
}

int String::length()
{
    return m_length;
}

const char *String::str() const
{
    return m_str;
}

bool String::operator ==(const String& s) const
{
    return (*this == s.m_str);
}

bool String::operator ==(const char* s) const
{
    return (strcmp(m_str, NULL_TO_BLANK(s)) == 0);
}

bool String::operator !=(const String& s) const
{
    return !(*this == s);
}

bool String::operator !=(const char* s) const
{
    return !(*this == s);
}

bool String::operator >(const String& s) const
{
    return (*this > s.m_str);
}

bool String::operator >(const char* s) const
{
    return (strcmp(m_str, NULL_TO_BLANK(s)) > 0);
}

bool String::operator <(const String& s) const
{
    return (*this < s.m_str);
}

bool String::operator <(const char* s) const
{
    return (strcmp(m_str, NULL_TO_BLANK(s)) < 0);
}

bool String::operator >=(const String& s) const
{
    return (*this >= s.m_str);
}

bool String::operator >=(const char* s) const
{
    return (strcmp(m_str, NULL_TO_BLANK(s)) >= 0);
}

bool String::operator <=(const String& s) const
{
    return (*this <= s.m_str);
}

bool String::operator <=(const char* s) const
{
    return (strcmp(m_str, NULL_TO_BLANK(s)) <= 0);
}

String String::operator + (const String& s) const
{
    return (*this + s.m_str);
}

String String::operator + (const char* s) const
{
    String ret;

    int len = strlen(NULL_TO_BLANK(s));
    char* str = reinterpret_cast<char*>(malloc(m_length + len + 1));
    if (str != NULL) {
        strcpy(str, m_str);//会复制结束符
        strcat(str, NULL_TO_BLANK(s));//会复制结束符

        free(ret.m_str);

        ret.m_str = str;
        ret.m_length = m_length + len;
    }
    else {
        THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory...");
    }

    return ret;
}

String& String::operator += (const String& s)
{
     return (*this = *this + s);
}

String& String::operator += (const char* s)
{
    return (*this = *this + s);
}

String& String::operator = (const String& s)
{
    if (this != &s) {
        *this = s.m_str;
    }
    return *this;
}

String& String::operator = (const char* s)
{
    if (m_str != s)
    {
        char* str = strdup(NULL_TO_BLANK(s));//用这个直接赋值字符串比较好一些
        if (str != NULL) {
            free(m_str);

            m_str = str;
            m_length = strlen(str);
        }
        else {
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory...");
        }

    }
    return *this;
}

String& String::operator = (char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

char& String::operator [] (int i)//这个应该首先定义，然后const函数来复用
{
    if (i >=0 && i < m_length)
    {
        return m_str[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "invalid index...");
    }

}

char String::operator [] (int i) const
{
    //return (const_cast<String&>(*this))[i];为啥要这样做呢
    return (*this)[i];//因为返回的是值，所以这样应该就可以了
}

bool String::startWith(const char* s) const
{
    bool ret = (s != NULL);
    if (ret)
    {
        int len = strlen(s);
        ret = (len <= m_length) && (strncmp(m_str, s, len) == 0);
    }
    return ret;
}

bool String::startWith(const String& s) const
{
   return startWith(s.m_str);
}

bool String::endOf(const char* s) const
{
    bool ret = (s != NULL);
    if (ret)
    {
        int len = strlen(s);
        //注意这里相等也是可以的
        ret = (len <= m_length) && (strncmp(m_str + m_length - len, s, len) == 0);
    }
    return ret;
}

bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int i, const char* s)
{
    if (i >=0 && i <= m_length)//注意这里插入index可以等于长度
    {
        if (s != NULL && *s != '\0')//这里不是生成字符串，所以还是要判断空和空字符串
        {
            int len = strlen(s);
            char* str = (char*)malloc(m_length + len + 1);
            if (str != NULL)
            {
                strncpy(str, m_str, i);//后面如果用strcat如果这里i=0会出问题
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);//这个应该是会复制结束符的

                free(m_str);
                m_str = str;
                m_length = m_length + len;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "invalid index...");
    }
    return *this;
}

String& String::insert(int i, const String& s)
{
    return insert(i, s.m_str);
}

String& String::trim()
{
    if (m_length > 0)
    {
        int s = 0;
        int e = m_length - 1;

        while(m_str[s] == ' ') s++;
        while(m_str[e] == ' ') e--;

        if (s == 0)//如果前面没有空格，那么就不需要移动
        {
            m_str[e + 1] = '\0';
            m_length = e + 1;//注意这里的长度
        }
        else
        {
            strcpy(m_str, m_str + s);
            m_str[e - s + 1] = '\0';
            m_length = e - s + 1;//注意这里长度
        }
    }
    return *this;
}

String::~String()
{
    free(m_str);
}
