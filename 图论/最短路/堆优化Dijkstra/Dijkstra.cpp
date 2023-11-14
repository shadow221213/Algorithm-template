/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-14 18:18:58
 * @LastEditTime: 2023-11-14 19:53:08
 */

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

const int INF = 2e9;

class Dijkstra {
private:
    int n;
    vector<vector<pii>> g;
public:
    Dijkstra(int _n): n(_n) {
        g.resize(n);
    }
    void add(vector<vector<int>> &edges) {
        for( auto &e : edges ) {
            int from = e[0], to = e[1], w = e[2];
            g[from].push_back({ to, w });
            g[to].push_back({ from, w });
        }
    }
    vector<int> dijkstra(int x) {
        vector<int> dis(n, INF);
        vector<bool> vis(n, false);
        priority_queue<pii, vector<pii>, greater<pii>> q;

        dis[x] = 0;
        q.push({ 0, x });
        while( !q.empty( ) ) {
            int u = q.top( ).second;
            q.pop( );

            if( vis[u] ) continue;

            vis[u] = true;
            for( int i = 0, m = g[u].size( ); i < m; i++ ) {
                int v = g[u][i].first;
                dis[v] = min(dis[v], dis[u] + g[u][i].second);
                q.push({ dis[v], v });
            }
        }

        return dis;
    }
};

class Solution {
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        Dijkstra dij(n);
        dij.add(edges);

        int ans = -1, cnt = INF;
        for( int i = 0; i < n; i++ ) {
            vector<int> dis = dij.dijkstra(i);
            int cur = 0;
            for( auto &d : dis )
                if( d <= distanceThreshold ) cur++;

            if( cnt >= cur ) {
                cnt = cur;
                ans = i;
            }
        }

        return ans;
    }
};
