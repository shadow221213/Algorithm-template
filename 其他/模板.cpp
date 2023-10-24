//edit by shadow221213
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;	//%Lf
using ui = unsigned int;
using ull = unsigned long long;	//%llu
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define pn putchar('\n')
#define NO puts("NO")
#define YES puts("YES")
#define mp(x, y) make_pair(x, y)
#define all(x) (x).begin(), (x).end()
#define Sum(x) accumulate(all(x), 0)
#define Mul(x) accumulate(all(x), 1, multiplies<ll>())
#define Max(x,n) max_element((x)+1, (x)+(n)+1) - (x)
#define Min(x,n) min_element((x)+1, (x)+(n)+1) - (x)
#define low(x,a) lower_bound(all(x), (a)) //>=a的第一个元素
#define upp(x,a) upper_bound(all(x), (a)) //>a的第一个元素
#define vclr(x,n) for(int i = 0; i <= n; i++) x[i].clear();

const ll LLF = 9e18;
const ull ULF = 1e19;
const int INF = 2e9;
const ui UIF = 4e9;
const ld PI = acosl(-1);
const int hashCnt = 3;
const int hashNum[5] = { 31,131,1331,13331 };
const ll hashMod[5] = { 1610612741,402653189,201326611,998244353 };

template<typename T> inline void Swap(T& a, T& b) { b ^= a ^= b ^= a; }
template<typename T> inline void Init(T* x, T y, T z) { memset(x, y, sizeof(T) * z); }
template<typename T> inline bool Cmax(T& x, T y) { return x < y ? x = y, 1 : 0; }
template<typename T> inline bool Cmin(T& x, T y) { return x > y ? x = y, 1 : 0; }
template<typename T> inline T GCD(T a, T b) {
    if( a == 1 || b == 1 ) return 1;
    while( b ^= a ^= b ^= a %= b ); return a;
}
template<typename T> inline T LCM(T a, T b) { return 1ll * a * b / GCD(a, b); }
template <typename T> inline T read( ) {
    int f = 1;
    T sum = 0;
    char ch = getchar( );
    while( !isdigit(ch) ) {
        if( ch == '-' ) f = -1;
        ch = getchar( );
    }
    while( isdigit(ch) ) {
        sum = (sum << 1) + (sum << 3) + (ch ^ 48);
        ch = getchar( );
    }
    return sum * f;
}
template <typename T> inline T readMod(int p) {
    int f = 1;
    T sum = 0;
    char ch = getchar( );
    while( !isdigit(ch) ) {
        if( ch == '-' ) f = -1;
        ch = getchar( );
    }
    while( isdigit(ch) ) {
        sum = ((sum << 1) % p + (sum << 3) % p + (ch ^ 48)) % p;
        ch = getchar( );
    }
    return sum * f < 0 ? p - sum : sum;
}
template < typename T > inline void read(T& x) {
    int f = 1;
    x = 0;
    char ch = getchar( );
    while( !isdigit(ch) ) {
        if( ch == '-' ) f = -1;
        ch = getchar( );
    }
    while( isdigit(ch) ) {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar( );
    }
    x = f * x;
}
template <typename T, typename... Args> inline void read(T& x, Args&... args) {
    read(x);
    read(args...);
}
template < typename T > inline void write(T x) {
    if( x < 0 ) {
        x = -x;
        putchar('-');
    }
    if( x > 9 ) write(x / 10);
    putchar(x % 10 + 48);
}

clock_t startTime, testTime;
inline double getCurrentTime( ) { return ( double )(clock( ) - startTime) * 1000 / CLOCKS_PER_SEC; }
inline ll lowbit(ll x) { return x & (-x); }
inline ull pow2(int i) { return 1ull << i; }
inline int ctz(ui x) { //求末尾0的数量
    if( !x ) return 32;
    int r = 31;
    x &= ~x + 1;
    if( x & 0x0000FFFF ) r -= 16;
    if( x & 0x00FF00FF ) r -= 8;
    if( x & 0x0F0F0F0F ) r -= 4;
    if( x & 0x33333333 ) r -= 2;
    if( x & 0x55555555 ) r -= 1;
    return r;
}
inline int ctzll(ull x) { //求末尾0的数量
    if( !x ) return 64;
    int r = 63;
    x &= ~x + 1;
    if( x & 0x00000000FFFFFFFF ) r -= 32;
    if( x & 0x0000FFFF0000FFFF ) r -= 16;
    if( x & 0x00FF00FF00FF00FF ) r -= 8;
    if( x & 0x0F0F0F0F0F0F0F0F ) r -= 4;
    if( x & 0x3333333333333333 ) r -= 2;
    if( x & 0x5555555555555555 ) r -= 1;
    return r;
}
inline int clz(ui x) { //求前导0的数量
    int r = 0;
    if( !(x & 0xFFFF0000) ) { r += 16; x <<= 16; }
    if( !(x & 0xFF000000) ) { r += 8; x <<= 8; }
    if( !(x & 0xF0000000) ) { r += 4; x <<= 4; }
    if( !(x & 0xC0000000) ) { r += 2; x <<= 2; }
    if( !(x & 0x80000000) ) { r += 1; x <<= 1; }
    return r;
}
inline int clzll(ull x) { //求前导0的数量
    int r = 0;
    if( !(x & 0xFFFFFFFF00000000) ) { r += 32; x <<= 32; }
    if( !(x & 0xFFFF000000000000) ) { r += 16; x <<= 16; }
    if( !(x & 0xFF00000000000000) ) { r += 8; x <<= 8; }
    if( !(x & 0xF000000000000000) ) { r += 4; x <<= 4; }
    if( !(x & 0xC000000000000000) ) { r += 2; x <<= 2; }
    if( !(x & 0x8000000000000000) ) { r += 1; x <<= 1; }
    return r;
}
inline ull gcd(ull a, ull b) { //调用前需fabs
    if( !a ) return b;
    if( !b ) return a;
    ull c = ctzll(a | b);
    a >>= ctzll(a);
    while( b ) {
        b >>= ctzll(b);
        if( a > b ) Swap(a, b);
        b -= a;
    }
    return a << c;
}

const int N = 2e5 + 5;
const int M = 1e2 + 5;
const int mod = 1e9 + 7;

int a[N];

inline void solve( ) {

}

signed main( ) {
    int _ = read<int>( );
    startTime = clock( );
    while( _-- )
        solve( );

    printf("%.0lf ms\n", getCurrentTime( ));
    return 0;
}