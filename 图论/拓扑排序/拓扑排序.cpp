#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

class TopolepicalSort {
private:
    int n;
    vector<int> in, dict;
    vector<vector<pii>> g;
public:
    TopolepicalSort(int _n) {
        n = _n;
        in.resize(n, 0);
        dict.resize(n, 1);
        g.resize(n);
    }
    void addEdge(int u, int v, int w) {
        g[u].push_back({ v, w }); // u->v
        in[v]++;
    }
    vector<int> topological_sort( ) {
        queue<int> q;
        vector<int> top;
        for( int i = 0; i < n; i++ )
            if( !in[i] ) q.push(i);

        while( !q.empty( ) ) {
            int u = q.front( );
            q.pop( );
            top.push_back(u);
            for( auto& [v, w] : g[u] ) {
                dict[v] = max(dict[v], dict[u] + w);
                if( --in[v] == 0 ) q.push(v);
            }
        }

        return top;
    }
};
