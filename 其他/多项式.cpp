/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-17 21:52:20
 * @LastEditTime: 2023-10-22 02:29:17
 */
#include<bits/stdc++.h>

#define all(x) x.begin(), x.end()

using namespace std;
using ui = unsigned int;
using poly = vector<int>;

// 求前导0的数量
inline int clz(ui x) {
    int r = 0;
    if( !(x & 0xFFFF0000) ) { r += 16; x <<= 16; }
    if( !(x & 0xFF000000) ) { r += 8; x <<= 8; }
    if( !(x & 0xF0000000) ) { r += 4; x <<= 4; }
    if( !(x & 0xC0000000) ) { r += 2; x <<= 2; }
    if( !(x & 0x80000000) ) { r += 1; x <<= 1; }
    return r;
}

namespace Poly {
    struct loop {
        int len, id;
        loop(int _len = 0, int _id = 0):len(_len), id(_id) { }
        bool operator < (const loop& a)const { return len > a.len; }
    };
    priority_queue<loop> q;
    int inv[N << 1], fac[N << 1], ifac[N << 1];
    poly A[N << 2], B[N << 2], C[N << 2], ve[N];
    constexpr int P(998244353), G(3);
    inline int INIT(const int& n) { return 1 << (32 - clz(n - 1)); }
    inline int sum(const int& x, const int& y) { return x + y >= P ? x + y - P : x + y; }
    inline int sub(const int& x, const int& y) { return x < y ? x - y + P : x - y; }
    inline int mul(const int& x, const int& y, const int& p = P) { return 1ll * x * y % p; }
    inline int qpow(int a, int b = P - 2, const int& p = P) {
        int res = 1;
        while( b ) {
            if( b & 1 ) res = mul(res, a, p);
            a = mul(a, a, p);
            b >>= 1;
        }
        return res;
    }
    inline poly getW(const int& L) {
        int wn = qpow(G, P / L);
        poly w(L);
        w[L / 2] = 1;
        for( int i = (L >> 1) + 1; i < L; i++ )
            w[i] = mul(wn, w[i - 1]);
        for( int i = (L >> 1) - 1; i > 0; i-- )
            w[i] = w[i << 1];
        return w;
    }
    constexpr int wa(911660635), inv2(499122177), wa2(43291859);
    //int wa = qpow(G, P - 1 >> 2), inv2 = qpow(2, P - 2, P), wa2 = wa * inv2 % mod;
    poly w = getW(1 << 18);
    inline poly dft(poly a, const int& n) {
        for( int k = n >> 1; k; k >>= 1 )
            for( int i = 0; i < n; i += k << 1 )
                for( int j = 0; j < k; j++ ) {
                    int y = a[i + j + k];
                    a[i + j + k] = mul(sub(a[i + j], y), w[j + k]);
                    a[i + j] = sum(a[i + j], y);
                }
        return a;
    }
    inline poly idft(poly a, const int& n) {
        for( int k = 1; k < n; k <<= 1 )
            for( int i = 0; i < n; i += k << 1 )
                for( int j = 0; j < k; j++ ) {
                    int x = a[i + j], y = mul(a[i + j + k], w[j + k]);
                    a[i + j] = sum(x, y);
                    a[i + j + k] = sub(x, y);
                }
        for( int i = 0, inv = P - (P - 1) / n; i < n; i++ )
            a[i] = mul(a[i], inv);
        reverse(a.begin( ) + 1, a.begin( ) + n);
        return a;
    }
    inline poly operator * (poly a, const int& b) {
        int n = a.size( );
        for( int i = 0; i < n; i++ )
            a[i] = mul(a[i], b);
        return a;
    }
    inline poly operator * (poly a, poly b) {
        int n = a.size( ), m = b.size( );
        int len = n + m - 1;
        if( n <= 8 || m <= 8 ) {
            poly c(len);
            for( int i = 0; i < n; i++ )
                for( int j = 0; j < m; j++ )
                    c[i + j] = sum(c[i + j], mul(a[i], b[j]));
            return c;
        }
        //int lim = 1 << (int)log2(len - 1) + 1;
        int lim = INIT(len);
        a.resize(lim);
        b.resize(lim);
        a = dft(a, lim);
        b = dft(b, lim);
        for( int i = 0; i < lim; i++ )
            a[i] = mul(a[i], b[i]);
        a = idft(a, lim);
        a.resize(len);
        return a;
    }
    inline poly operator + (poly a, poly b) {
        int n = b.size( );
        a.resize(max(( int )a.size( ), n));
        for( int i = 0; i < n; i++ )
            a[i] = sum(a[i], b[i]);
        return a;
    }
    inline poly operator - (poly a, poly b) {
        int n = b.size( );
        a.resize(max(( int )a.size( ), n));
        for( int i = 0; i < n; i++ )
            a[i] = sum(a[i], P - b[i]);
        return a;
    }
    inline poly shift(poly a, const int& x) {
        if( x < 0 ) return -x > a.size( ) ? poly( ) : poly(a.begin( ) - x, a.end( ));
        a.insert(a.begin( ), x, 0);
        return a;
    }
    inline poly polyInv(const poly& a, const int& n) {
        if( n == 1 ) {
            poly b(1);
            b[0] = qpow(a[0], P - 2);
            return b;
        }
        poly b = polyInv(a, (n + 1) / 2);
        poly c = poly(a.begin( ), a.begin( ) + min(n, int(a.size( ))));
        //int len = 1 << (int)log2(2 * n - 1) + 1;
        int len = INIT(n << 1);
        b.resize(len);
        c.resize(len);
        b = dft(b, len);
        c = dft(c, len);
        for( int i = 0; i < len; i++ )
            b[i] = mul(sub(2, mul(b[i], c[i])), b[i]);
        b = idft(b, len);
        b.resize(n);
        return b;
    }
    inline poly polySqrt(const poly& a, const int& n) {
        poly b { a[0] }, c;
        for( int l = 4; (l >> 2) < n; l <<= 1 ) {
            int r = l >> 1;
            b.resize(r);
            c = poly(a.begin( ), a.begin( ) + min(r, ( int )a.size( ))) * polyInv(b, r);
            for( int j = 0; j < r; j++ )
                b[j] = mul(sum(c[j], b[j]), inv2);
        }
        b.resize(n);
        return b;
    }
    inline poly Derivation(poly a) {
        int n = a.size( );
        if( !n ) return a;
        for( int i = 0; i + 1 < n; i++ )
            a[i] = mul(a[i + 1], i + 1);
        a.pop_back( );
        return a;
    }
    inline poly Integral(poly a) {
        int n = a.size( );
        for( int i = 0; i < n; i++ )
            a[i] = mul(a[i], inv[i + 1]);
        a.insert(a.begin( ), 0);
        return a;
    }
    inline poly polyLn(poly a, const int& n) {
        a = Integral(Derivation(a) * polyInv(a, n));
        a.resize(n);
        return a;
    }
    inline poly polyExp(poly a, const int& n) {
        if( n == 1 ) {
            poly b;
            b.push_back(1);
            return b;
        }
        poly b = polyExp(a, (n + 1) / 2);
        poly c = b;
        b = polyLn(b, n);
        int m = b.size( );
        if( a.size( ) < m ) a.resize(m);
        for( int i = 0; i < m; i++ )
            b[i] = sum(sub((i == 0), b[i]), a[i]);
        b = b * c;
        b.resize(n);
        return b;
    }
    inline poly polyPow(poly a, const int& n, const int& b) {
        a = polyExp(polyLn(a, n) * b, n);
        a.resize(n);
        return a;
    }
    inline poly operator /  (poly a, poly b) {
        int len = 1, deg = a.size( ) - b.size( ) + 1;
        reverse(all(a));
        reverse(all(b));
        while( len <= deg )
            len <<= 1;
        b = polyInv(b, len);
        b.resize(deg);
        a = a * b;
        a.resize(deg);
        reverse(all(a));
        return a;
    }
    inline poly operator % (const poly& a, const poly& b) {
        poly c = a - (a / b) * b;
        c.resize(b.size( ) - 1);
        return c;
    }
    inline poly operator ^ (const poly& a, poly b) {
        int n = a.size( ), m = b.size( );
        reverse(all(b));
        b = b * a;
        b.resize(n + m);
        poly ans(n);
        for( int i = 0; i < n; i++ )
            ans[i] = b[i + m - 1];
        return ans;
    }
    inline poly operator << (const poly& a, const int& n) {
        int m = a.size( );
        int len = n + m;
        poly ans(len);
        for( int i = len - 1, j = m - 1; j >= 0; i--, j-- )
            ans[i] = a[j];
        return ans;
    }
    inline poly polySin(poly a, const int& n) {
        //a.resize(n);
        a = (polyExp(a * wa, n) - polyExp(a * (P - wa), n)) * wa2;
        return a;
    }
    inline poly polyCos(poly a, const int& n) {
        //a.resize(n);
        a = (polyExp(a * wa, n) + polyExp(a * (P - wa), n)) * inv2;
        return a;
    }
    inline poly polytan(const poly& a, const int& n) {
        poly c = polySin(a, n) / polyCos(a, n);
        return c;
    }
    inline poly polyAsin(const poly& a, const int& n) {
        poly b, c, d;
        b = Derivation(a);
        c = a * a;
        for( int i = 0; i < n; i++ )
            c[i] = sub(P, c[i]);
        c[0] = sum(c[0], 1);
        d = polySqrt(c, n);
        d = polyInv(d, n);
        d = b * d;
        d = Integral(d);
        return d;
    }
    inline poly polyAcos(const poly& a, const int& n) {
        poly b = polyAsin(a, n);
        for( int i = 0; i < n; i++ )
            b[i] = sub(P, b[i]);
        return b;
    }
    inline poly polyAtan(const poly& a, const int& n) {
        poly b, c, d;
        b = Derivation(a);
        c = a * a;
        c[0] = sum(c[0], 1);
        d = polyInv(c, n);
        d = b * d;
        d = Integral(d);
        return d;
    }
    // 多点取值
    inline poly MultiPoint(poly f, poly g) {
        int n = max(f.size( ), g.size( )), m = g.size( );
        f.resize(n);
        g.resize(n);
        function<void(int, int, int)> build = [&] (int k, int l, int r) {
            if( l == r ) {
                A[k] = poly { 1,(P - g[l]) % P };
                return;
            }
            int mid = (l + r) >> 1;
            build(k << 1, l, mid);
            build(k << 1 | 1, mid + 1, r);
            A[k] = A[k << 1] * A[k << 1 | 1];
            };
        build(1, 0, n - 1);
        poly ans(n);
        function<void(int, int, int, poly)> calc = [&] (int k, int l, int r, poly F) {
            F.resize(r - l + 1);
            if( l == r ) {
                ans[l] = F[0];
                return;
            }
            int mid = (l + r) >> 1;
            calc(k << 1, l, mid, F ^ A[k << 1 | 1]);
            calc(k << 1 | 1, mid + 1, r, F ^ A[k << 1]);
            };
        calc(1, 0, n - 1, f ^ polyInv(A[1], A[1].size( )));
        ans.resize(m);
        return ans;
    }
    inline poly fdt(poly a, const int& n) {
        poly b(n);
        for( int i = 0; i < n; i++ )
            b[i] = ifac[i];
        a = a * b;
        a.resize(n);
        for( int i = 0; i < n; i++ )
            a[i] = mul(a[i], fac[i]);
        return a;
    }
    inline poly ifdt(poly a, const int& n) {
        poly b(n);
        for( int i = 0; i < n; i++ )
            a[i] = mul(a[i], ifac[i]);
        for( int i = 0; i < n; i++ )
            if( i & 1 ) b[i] = P - ifac[i];
            else b[i] = ifac[i];
        a = a * b;
        a.resize(n);
        return a;
    }
    inline poly FDT(poly a, poly b) {
        int len = a.size( ) + b.size( ) - 1;
        a.resize(len);
        b.resize(len);
        a = fdt(a, len);
        b = fdt(b, len);
        for( int i = 0; i < len; i++ )
            a[i] = mul(a[i], b[i]);
        a = ifdt(a, len);
        a.resize(len);
        return a;
    }
    inline poly toFDT(const poly& a, const int& n) {
        poly b(n);
        for( int i = 0; i < n; i++ )
            b[i] = i;
        poly c = MultiPoint(a, b);
        c = ifdt(c, n);
        return c;
    }
    // 结果为C[1]
    inline void FDTto(const poly& a, const int& p, const int& l, const int& r) {
        if( l == r ) {
            B[p] = poly({ P - l , 1 });
            C[p] = poly({ a[l] });
            return;
        }
        int mid = (l + r) >> 1;
        FDTto(a, p << 1 | 1, mid + 1, r);
        FDTto(a, p << 1, l, mid);
        B[p] = B[p << 1] * B[p << 1 | 1];
        C[p] = C[p << 1] + C[p << 1 | 1] * B[p << 1];
    }
    // b从1读入
    inline void CDQ(poly& a, const poly& b, int l, int r) {
        if( l + 1 == r ) return;
        int mid = l + r >> 1;
        CDQ(a, b, l, mid);
        poly c(a.begin( ) + l, a.begin( ) + mid), d(b.begin( ), b.begin( ) + r - l);
        poly t = c * d;
        for( int i = mid; i < r; i++ )
            a[i] = (a[i] + t[i - l]) % P;
        CDQ(a, b, mid, r);
    }
    // 启发式合并，一般为环，拿长度排序，可在排序前使用random_shuffle
    inline void convolution(int u, int v) {
        int n = ve[u].size( ), m = ve[v].size( );
        poly a(n), b(m);
        for( int i = 0; i < n; i++ )
            a[i] = ve[u][i];
        for( int i = 0; i < m; i++ )
            b[i] = ve[v][i];
        a = a * b;
        int lim = n + m - 1;
        ve[u].resize(lim);
        for( int i = 0; i < lim; i++ )
            ve[u][i] = a[i];
    }
    inline int calc(int n) {
        while( q.size( ) > 1 ) {
            int u = q.top( ).id;
            q.pop( );
            int v = q.top( ).id;
            q.pop( );
            convolution(u, v);
            q.push(loop(ve[u].size( ), u));
        }
        poly& g = ve[q.top( ).id];
        q.pop( );
        int ans = 0;
        for( int i = 0; i < g.size( ); i++ )
            ans = i & 1 ? sub(ans, mul(fac[n - i], g[i])) : sum(ans, mul(fac[n - i], g[i]));
        return ans;
    }
    // ex时预处理
    inline void initInv(const int& n) {
        inv[0] = inv[1] = 1;
        for( int i = 2; i <= n; i++ )
            inv[i] = mul(inv[P % i], P - P / i);
    }
    inline void initF(const int& n) {
        fac[0] = 1;
        for( int i = 1; i <= n; i++ )
            fac[i] = mul(fac[i - 1], i);
        ifac[n] = qpow(fac[n]);
        for( int i = n; i >= 1; i-- )
            ifac[i - 1] = mul(ifac[i], i);
    }
}

using namespace Poly;