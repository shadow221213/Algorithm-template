/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-04 13:55:46
 * @LastEditTime: 2023-11-04 15:15:21
 */
#include <bits/stdc++.h>
using namespace std;

class Trie {
private:
    struct node {
        node *children[2];

        node(node *_l = nullptr, node *_r = nullptr): children { _l, _r } { }
    };
public:
    node *root;

    Trie(node *_l = nullptr, node *_r = nullptr): root(new node(_l, _r)) { }
    void insert(int x) {
        node *tmp = root;
        for( int i = 30; ~i; i-- ) {
            int v = x >> i & 1;
            if( !tmp->children[v] ) tmp->children[v] = new node( );

            tmp = tmp->children[v];
        }
    }
    int search(int x) {
        int ans = 0;
        node *tmp = root;
        for( int i = 30; ~i; i-- ) {
            int v = x >> i & 1;
            if( tmp->children[v ^ 1] ) {
                ans |= 1 << i;
                tmp = tmp->children[v ^ 1];
            }
            else tmp = tmp->children[v];
        }

        return ans;
    }
};

class Solution {
private:
    Trie trie;
public:
    int findMaximumXOR(vector<int> &nums) {
        int ans = 0;
        for( auto &x : nums ) {
            trie.insert(x);
            ans = max(ans, trie.search(x));
        }

        return ans;
    }
};

signed main( ) {
    Solution solve;
    vector<int> nums = { 3, 10, 5, 25, 2, 8 };
    printf("%d\n", solve.findMaximumXOR(nums));
    return 0;
}
