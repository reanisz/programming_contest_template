#pragma once

#include "interval.h"

template<class T>
class rectangle{
public:
    complex<T> pos;
    complex<T> size;
    rectangle()
        : pos(), size()
    {
    }
    rectangle(const T& _x, const T& _y, const T& _w, const T& _h)
        : pos(_x,_y), size(_w, _h)
    {
    }

    T& x(){
        return pos.real();
    }
    T& y(){
        return pos.imag();
    }
    T& w(){
        return size.real();
    }
    T& h(){
        return size.imag();
    }
    const T x() const{
        return pos.real();
    }
    const T y() const{
        return pos.imag();
    }
    const T w() const{
        return size.real();
    }
    const T h() const{
        return size.imag();
    }

    complex<T> pos1() const{
        return pos;
    }
    complex<T> pos2() const{
        return pos + size - complex<T>{1,1};
    }

    interval<T> dx() const{
        return hull(x(), x() + w() - 1);
    }
    interval<T> dy() const{
        return hull(y(), y() + h() - 1);
    }

    bool contains(const complex<T>& v) const{
        return dx().contains(v.real()) && dy().contains(v.imag());
    }
};

template<class T>
ostream& operator<<(ostream& os, const rectangle<T>& v)
{
    os << v.pos1() << " - " << v.pos2() << " [" << v.size.real() << "x" << v.size.imag() << "]";
    return os;
}

template<class T>
maybe<rectangle<T>> intersect(const rectangle<T>& a, const rectangle<T>& b){
    auto ix = intersect(a.dx(), b.dx());
    auto iy = intersect(a.dy(), b.dy());
    cout << ix << endl << iy << endl;
    if(ix && iy){
        return rectangle<T>(ix->left,iy->left, ix->right - ix->left + 1,iy->right - iy->left + 1);
    }
    return none;
}
