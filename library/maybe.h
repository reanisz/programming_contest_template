#pragma once

struct maybe_none_type{
    maybe_none_type(){}
};

const maybe_none_type none;

template<class T>
class maybe{
    typename std::aligned_storage<sizeof(T), alignof(T)>::type value;
    T* ptr;
public:
    maybe()
        : ptr(nullptr)
    {
    }
    maybe(const maybe_none_type& t)
        : ptr(nullptr)
    {
    }
    maybe(const T& v)
    {
        ptr = new(&value) T(v);
    }
    ~maybe(){
        ptr->~T();
        //T::operator delete(ptr, &value);
    }

    operator bool() const{
        return ptr != nullptr;
    }
    T& operator*(){
        return *ptr;
    }
    const T& operator*() const{
        return *ptr;
    }
    T* operator->(){
        return ptr;
    }
    T* const operator->() const{
        return ptr;
    }
};

template<class T>
ostream& operator<<(ostream& os, const maybe<T>& v)
{
    if(v){
        os << *v;
    }else{
        os << "(none)";
    }
    return os;
}
