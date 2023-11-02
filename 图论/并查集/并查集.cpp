/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-22 02:25:12
 * @LastEditTime: 2023-11-02 15:12:22
 */
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

class unionFind {
private:
    vector<int> fa, sz;
public:
    unionFind(int n): fa(n), sz(n, 1) {
        iota(all(fa), 0);
    }
    int find(int x) {
        if( fa[x] == x ) return x;
        else return fa[x] = find(fa[x]);
    }
    void push(int x, int y) {
        int rx = find(x), ry = find(y);
        if( rx != ry ) {
            if( sz[rx] > sz[ry] ) {
                fa[ry] = rx;
                sz[rx] += sz[ry];
            }
            else {
                fa[rx] = ry;
                sz[ry] += sz[rx];
            }
        }
    }
    int getSize(int x) {
        return sz[x];
    }
};

class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        unionFind uf(n);
        for( auto& edge : edges )
            uf.push(edge[0], edge[1]);

        long long res = 0;
        for( int i = 0; i < n; i++ )
            res += n - uf.getSize(uf.find(i));

        return res / 2;
    }
};