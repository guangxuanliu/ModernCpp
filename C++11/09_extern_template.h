#ifndef _EXTERN_TEMPLATE_H_
#define _EXTERN_TEMPLATE_H_

template <typename T>
class MyClass
{
public:
    void set(T t) { m_val = t; }
    T get() { return m_val; }
private:
    T m_val;
};

// 如果是类模板，需要加class关键字
// 如果是函数模板，则去掉class关键字
extern template class MyClass<int>;

#endif // !
