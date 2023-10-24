/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-22 02:25:12
 * @LastEditTime: 2023-10-24 19:47:59
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()

class unionFind {
private:
    vector<int> parents, sizes;
public:
    unionFind(int n): parents(n), sizes(n, 1) {
        iota(all(parents), 0);
    }
    int find(int x) {
        if( parents[x] == x ) return x;
        else return parents[x] = find(parents[x]);
    }
    void push(int x, int y) {
        int rx = find(x), ry = find(y);
        if( rx != ry ) {
            if( sizes[rx] > sizes[ry] ) {
                parents[ry] = rx;
                sizes[rx] += sizes[ry];
            }
            else {
                parents[rx] = ry;
                sizes[ry] += sizes[rx];
            }
        }
    }
    int getSize(int x) {
        return sizes[x];
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

// 例题：
// 2316.统计无向图中无法互相到达点对数