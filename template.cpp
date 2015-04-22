#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <functional>
#include <sstream>
#include <complex>
#include <regex>
#include <cmath>
#include <bitset>
#include <array>
#include <deque>
#include <list>
#include <stack>
#include <iterator>
#include <random>

using namespace std;

extern void* enabler;

//-----桁指定出力-------
// %8d: cout << setw(8);
// %08d: cout << setw(8) << setfill('0');

//=====別名・定数定義=====

using LL=long long int;
using ULL=unsigned long long int;
using Complex=complex<double>;

template<class T>
using asc_pqueue=std::priority_queue<T,vector<T>, std::greater<T>>;
template<class T>
using desc_pqueue=std::priority_queue<T,vector<T>, std::less<T>>;
template<class T>
using asc_set=std::set<T,vector<T>, std::greater<T>>;
template<class T>
using desc_set=std::set<T,vector<T>, std::less<T>>;

const LL INF = (1ll << 62);

//#include "library/graph.h"
//#include "library/interval.h"
//#include "library/maybe.h"
//#include "library/utility.h"
//#include "library/rectangle.h"
//#include "library/bit.h"

//==========

int main(){
    return 0;
}

