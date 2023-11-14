/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-14 18:18:58
 * @LastEditTime: 2023-11-14 19:32:09
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 2e9;
const int M = 1e9 + 5;

class Floyd {
public:
    vector<vector<int>> g;

    Floyd(int n) {
        g.resize(n, vector<int>(n, M));
        for( int i = 0; i < n; i++ )
            g[i][i] = 0;
    }
    void add(vector<vector<int>> &edges) {
        for( auto &e : edges ) {
            int from = e[0], to = e[1], w = e[2];
            g[from][to] = g[to][from] = w;
        }
    }
    void floyd( ) {
        int n = g.size( );
        for( int p = 0; p < n; p++ )
            for( int i = 0; i < n; i++ )
                for( int j = 0; j < n; j++ )
                    g[i][j] = min(g[i][j], g[i][p] + g[p][j]);
    }
};

class Solution {
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        Floyd floyd(n);
        floyd.add(edges);
        floyd.floyd( );

        int ans = -1, cnt = INF;
        for( int i = 0; i < n; i++ ) {
            int cur = 0;
            for( int j = 0; j < n; j++ )
                if( i != j && floyd.g[i][j] <= distanceThreshold ) cur++;

            cout << cur << endl;

            if( cnt >= cur ) {
                cnt = cur;
                ans = i;
            }
        }

        return ans;
    }
};