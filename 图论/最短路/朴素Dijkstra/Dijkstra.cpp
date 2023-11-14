/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-14 18:18:58
 * @LastEditTime: 2023-11-14 20:05:13
 */

#include <bits/stdc++.h>
using namespace std;

const int M = 1e9 + 5;

class Dijkstra {
private:
    int n;
    vector<vector<int>> g;
public:
    Dijkstra(int _n): n(_n) {
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
    vector<int> dijkstra(int x) {
        vector<int> dis(n, M);
        vector<bool> vis(n, false);

        dis[x] = 0;
        for( int k = 0; k < n; k++ ) {
            int t = -1;
            for( int i = 0; i < n; i++ )
                if( !vis[i] && (t == -1 || dis[i] < dis[t]) ) t = i;

            vis[t] = true;
            for( int i = 0; i < n; i++ )
                dis[i] = min(dis[i], dis[t] + g[t][i]);
        }

        return dis;
    }
};

class Solution {
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        Dijkstra dij(n);
        dij.add(edges);

        int ans = -1, cnt = M;
        for( int i = 0; i < n; i++ ) {
            vector<int> dis = dij.dijkstra(i);
            int cur = 0;
            for( auto &d : dis )
                if( d <= distanceThreshold ) cur++;

            if( cur <= cnt ) {
                cnt = cur;
                ans = i;
            }
        }

        return ans;
    }
};
