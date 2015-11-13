#pragma once
#include <algorithm>
#include <utility>

//=====debug======
#define debug(...) cerr << __VA_ARGS__ << endl;

template<typename T>
class has_begin_and_end
{
    private:
    template<typename U>
    static auto check( U v ) -> decltype( v.begin(), v.end(), std::true_type() );
    static auto check( ... ) -> decltype( std::false_type() );

    public:
    typedef decltype( check( std::declval<T>() ) ) type;
    static bool const value = type::value;
};
template<typename T>
class has_top_and_pop
{
    private:
    template<typename U>
    static auto check( U v ) -> decltype( v.empty(), v.top(), v.pop(), std::true_type() );
    static auto check( ... ) -> decltype( std::false_type() );

    public:
    typedef decltype( check( std::declval<T>() ) ) type;
    static bool const value = type::value;
};
template<typename T>
class has_front_and_pop
{
    private:
    template<typename U>
    static auto check( U v ) -> decltype( v.empty(), v.front(), v.pop(), std::true_type() );
    static auto check( ... ) -> decltype( std::false_type() );

    public:
    typedef decltype( check( std::declval<T>() ) ) type;
    static bool const value = type::value;
};

template<class T, typename std::enable_if<has_begin_and_end<T>::value>::type*& = enabler>
void dump(const T& val){
    for(auto& v : val){
        debug(v);
    }
}
template<class T, typename std::enable_if<has_top_and_pop<T>::value>::type*& = enabler>
void dump(T val){
    while(!val.empty()){
        debug(val.top());
        val.pop();
    }
}
template<class T, typename std::enable_if<has_front_and_pop<T>::value>::type*& = enabler>
void dump(T val){
    while(!val.empty()){
        debug(val.front());
        val.pop();
    }
}

//=====pair-utility=====

template<class T, class U>
ostream& operator<<(ostream& os, const pair<T,U>& v)
{
    os << "(" <<  v.first <<  ", " << v.second << ")";
    return os;
}

template<class T, class U>
istream& operator>>(istream& is, pair<T,U>& v)
{
    is >> v.first;
    is >> v.second;
    return is;
}

#define def_pair_op(op) template<class T, class U> \
auto operator op(const pair<T,U>& a, const pair<T,U>& b) -> pair<decltype(a.first op b.first), decltype(a.second op b.second)> \
{ \
    return make_pair(a.first op b.first,a.second op b.second); \
} \
template<class T, class U, class V> \
auto operator op(const pair<T,U>& a, V b) -> pair<decltype(a.first op b), decltype(a.second op b)> \
{ \
    return make_pair(a.first op b, a.second op b); \
}

def_pair_op(+)
def_pair_op(-)
def_pair_op(*)
def_pair_op(/)
def_pair_op(%)
#undef def_pair_op


//=====clamp=====

template<class T>
T clamp(const T& val, const T& a, const T& b){
    return min(a, max(val, b));
}

template<class T,class U>
pair<T,U> clampPair(const pair<T,U>& val, const pair<T,U>& a, const pair<T,U>& b){
    return {clamp(val.first,a.first,b.first), clamp(val.second,a.second,b.second)};
}

//=====hash=====

template<std::size_t... idx>
struct index_sequence{
        typedef index_sequence<idx..., sizeof...(idx)> next;
            static constexpr size_t size() { return sizeof...(idx); }
};

template<std::size_t idx>
struct build_tuple{
        typedef typename build_tuple<idx-1>::type::next type;
};

template<>
struct build_tuple<0>{
        typedef index_sequence<> type;
};


template<std::size_t N>
using make_index_sequence = typename build_tuple<N>::type;
    

namespace std {
    template<class... T>
        class hash<std::tuple<T...>> {
            template<size_t... I>
                size_t impl(const std::tuple<T...>& t, ::index_sequence<I...>) const{
                    initializer_list<size_t> h{std::hash<typename std::tuple_element<I, std::tuple<T...>>::type>()(std::get<I>(t))...};
                    size_t a = accumulate(h.begin(), h.end(), 0, [](size_t a, size_t b){return a ^ b;});
                    return a;
                }
            public:
            size_t operator()(const std::tuple<T...> &t) const 
            {
                return impl(t, ::make_index_sequence<std::tuple_size<std::tuple<T...>>::value>());
            }
        };
}


//=====complex=====

template<class T>
bool operator<(const complex<T>& a, const complex<T>& b){
    if(a.real() == b.real())
        return a.imag() < b.imag();
    return a.real() < b.real();
}
template<class T>
bool operator>(const complex<T>& a, const complex<T>& b){
    if(a.real() == b.real())
        return a.imag() > b.imag();
    return a.real() > b.real();
}

//=====gcd/lcm

template<class T>
T gcd(const T& a, const T& b){
    return __gcd(a,b);
}

template<class T>
T lcm(const T& a, const T& b){
    return a*b/__gcd(a,b);
}

//===binary_search

template<class T>
maybe<T> lower_bound_if(const T& begin, const T& end, const std::function<bool(const T&)>& func){
    T low = begin;
    T high = end;
    while(1){
        T mid = low + (high - low) / 2;
//      cout << "(" << low << "," << high << ") -> " << mid <<endl;
        if(low == high){
            return low;
        }else if(high - low == 1){
            if(func(low)){
                return low;
            }else{
                return high;
            }
        }
        bool f = func(mid);
        if(f){
            high = mid;
        }else{
            low = mid;
        }
    }
}
