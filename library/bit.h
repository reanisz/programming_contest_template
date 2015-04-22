#pragma once

template<class T, class V = void*>
class binary_index_tree{
    function<void(T&)> upfunc;
    function<V(V&, const T&)> acfunc;
public:
    const int size;
    vector<T> data;

    binary_index_tree(int n, function<void(T&)> upfunc_)
        : size(n), data(n+1), upfunc(upfunc_)
    {
    }
    binary_index_tree(int n, function<void(T&)> upfunc_ ,function<V(V&, const T&)> acfunc_)
        : size(n), data(n+1), upfunc(upfunc_), acfunc(acfunc_)
    {
    }

    template<class U>
    U accumulate(int i, const U& init, function<U(U&,const T&)> func){
        U data = init;
        while(i>0){
            func(data,data[i]);
            i -= i & -i;
        }
        return data;
    }
    V accumulate(int i, const V& init){
        V data = init;
        while(i>0){
            func(data,data[i]);
            i -= i & -i;
        }
        return data;
    }

    //int sum(int i){
    //    return accumulate(i, 0, [](int& d, const int& t){ d += t;});
    //}
    
    void update(int i, const T& v){
        while(i <= size){
            upfunc(i, v);
            i += i & -i;
        }
    }
};
