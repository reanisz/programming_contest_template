#pragma once

#include "maybe.h"

template<class T>
struct interval{
public:
    T left;
    T right;
    interval(const T& l, const T& r)
        : left(min(l,r)), right(max(l,r))
    {
    }
    void update_left(const T& val){
        left = min(val,right);
        right = max(val,right);
    }
    void update_right(const T& val){
        right = max(val,left);
        left = min(val,left);
    }
    bool contains(const T& val){
        return left <= val && val <= right;
    }
};

#define def_interval_lop(op) template<class T> \
bool operator op(const interval<T>& a, const interval<T>& b) \
{ \
    return make_pair(a.left,a.right) op make_pair(b.left, b.right); \
} \

def_interval_lop(<)
def_interval_lop(<=)
def_interval_lop(>)
def_interval_lop(>=)
def_interval_lop(==)
def_interval_lop(!=)
#undef def_pair_op

template<class T>
maybe<interval<T>> intersect(const interval<T>& l, const interval<T>& r){
    if(l.left > r.left){
        return intersect(r,l);
    }
    if(l.left == r.left){
        return interval<T>(l.left, min(l.right,r.right));
    }
    cout << "--" << l << "," << r << endl;
    if(l.right < r.left){
        return none;
    }
    return interval<T>(r.left, l.right);
}

template<class T>
ostream& operator<<(ostream& os, const interval<T>& v)
{
    os << "[" <<  v.left <<  ", " << v.right << "]";
    return os;
}

template<class T>
interval<T> hull(const T& l, const T& r){
    return interval<T>(l,r);
}
