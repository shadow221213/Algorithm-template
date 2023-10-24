#include <bits/stdc++.h>

using namespace std;
using ll = long long;

inline void rightCode(vector<ll>& nums) {

}
inline void testCode(vector<ll>& nums) {

}
inline vector<ll> generateRandomVector(int size, int value) {
    srand(( ll )time(NULL));
    vector<ll> result(rand( ) % (size + 1));
    for( ll i = 0; i < result.size( ); i++ )
        result[i] = rand( ) % (value + 1);
    return result;
}
/*
    test_time 测试次数，设置比较大，排除特殊情况
    size 生成数组最大尺寸
    value 生成数组每个元素的最大值
*/
inline void test(ll test_time, ll size, ll value) {
    bool if_accept = true;
    for( ll i = 0; i < test_time; i++ ) {
        vector<ll> nums(generateRandomVector(size, value));
        vector<ll> nums1(nums);
        vector<ll> nums2(nums);
        rightCode(nums1);
        testCode(nums2);
        if( nums1 != nums2 ) {
            if_accept = false;
            for( auto c : nums )
                printf("%lld ", c);
            break;
        }
    }
    printf(if_accept ? "true!\n" : "false!\n");
}

signed main( ) {
    ll test_time, size, value;
    scanf("%lld %lld %lld", &test_time, &size, &value);
    test(test_time, size, value);
}
