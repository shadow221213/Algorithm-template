/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-11-06 18:05:33
 * @LastEditTime: 2023-11-07 19:36:40
 */
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define Max(x) max_element(all(x))

class Manacher {
private:
    int n;
    string s = "";
    vector<int> arm;
public:
    Manacher(string &st) {
        for( auto &c : st ) {
            s += c;
            s += '#';
        }

        n = s.size( );
        arm.resize(n, 0);
    }
    void manacher( ) {
        int  l = 0, r = -1;
        for( int i = 0; i < n; i++ ) {
            int k = i > r ? 1 : min(arm[l + r - i], r - i + 1);
            while( i >= k && i + k < n && s[i - k] == s[i + k] )
                k++;
            arm[i] = k--;

            if( i + k > r ) {
                l = i - k;
                r = i + k;
            }
        }
    }
    string getAns( ) {
        int left = Max(arm) - arm.begin( ), right = arm[left];
        string ans = "";
        for( int i = left - right + 1; i < left + right; i++ ) {
            if( s[i] == '#' ) continue;
            ans += s[i];
        }

        return ans;
    }
    vector<string> getAns2( ) {
        vector<string> ans;
        for( int i = 0; i < n; i++ ) {
            if( arm[i] == 0 ) continue;
            string res = "";
            for( int j = i - arm[i] + 1; j < i + arm[i]; j++ ) {
                if( s[j] == '#' ) continue;
                res += s[j];
            }
            ans.push_back(res);
        }

        return ans;
    }
};

class Solution {
public:
    string longestPalindrome(string s) {
        Manacher manacher(s);
        manacher.manacher( );
        return manacher.getAns( );
    }
};

signed main( ) {
    Solution solution;
    string str = "babad";
    Manacher manacher(str);
    manacher.manacher( );
    auto ans = manacher.getAns2( );
    for( auto &x : ans ) {
        cout << x << endl;
    }
}
