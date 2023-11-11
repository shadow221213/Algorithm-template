/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-01 14:21:02
 * @LastEditTime: 2023-11-11 19:56:51
 */
#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

class Loop {
private:
    int n;
    vector<vector<pii>> g;
public:
    Loop(int _n) {
        n = _n;
        g.resize(n);
    }
    void addEdge(int u, int v, int w) {
        g[u].push_back({ v, w }); // u->v
    }
    int loop( ) {
        int ans = 0;
        vector<bool> vis(n, false);

        for( int i = 0; i < n; i++ ) {
            if( vis[i] ) continue;

            int j = i, sz = 0;
            vector<int> cir;
            while( !vis[j] ) {
                cir.push_back(j);
                vis[j] = true;
                j = g[j][0].first;
                sz += g[j][0].second;
            }

            int m = cir.size( );
            for( int k = 0; k < m; k++ ) {
                if( cir[k] == j ) {
                    // 求解最大环
                    ans = max(ans, sz);
                    break;
                }
                else sz -= g[cir[k]][0].second;
            }
        }

        return ans;
    }
};