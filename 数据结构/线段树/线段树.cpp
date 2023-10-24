/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-09 19:31:02
 * @LastEditTime: 2023-10-22 02:27:25
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 5;
const int M = 3e4;
const int mod = 1e9 + 7;

class SegTree {
private:
    struct node {
        node* l;
        node* r;
        int val;
        int lazy;

        node(node* _l = NULL, node* _r = NULL, int _val = 0, int _lazy = 0): l(_l), r(_r), val(_val), lazy(_lazy) { }
    };
public:
    node root; // 需要外部调用根节点
    SegTree(int _val = 0): root(NULL, NULL, _val, 0) { }
    void pushUp(node& root) {
        root.val = (*root.l).val + (*root.r).val;
    }
    void pushDown(node& root, int l, int r) {
        if( root.l == NULL ) root.l = new node;
        if( root.r == NULL ) root.r = new node;

        if( root.lazy == 0 ) return;

        (*root.l).val += root.lazy * l;
        (*root.r).val += root.lazy * r;
        // 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
        (*root.l).lazy += root.lazy;
        (*root.r).lazy += root.lazy;
        root.lazy = 0;
    }
    void update(node& root, int start, int end, int l, int r, int val) {
        if( l <= start && end <= r ) {
            // 在此处修改区间[l, r]的值
            root.val = (end - start + 1) * val;
            root.lazy = val;
            return;
        }

        int mid = start + end >> 1;
        pushDown(root, mid - start + 1, end - mid);
        // cout << root.l << endl << root.r << endl;
        if( l <= mid ) update((*root.l), start, mid, l, r, val);
        if( r > mid ) update((*root.r), mid + 1, end, l, r, val);

        pushUp(root);
    }
    int query(node& root, int start, int end, int l, int r) {
        if( l <= start && end <= r ) return root.val;

        int mid = (start + end) >> 1, ans = 0;
        pushDown(root, mid - start + 1, end - mid);

        if( l <= mid ) ans += query((*root.l), start, mid, l, r);
        if( r > mid ) ans += query((*root.r), mid + 1, end, l, r);

        return ans;
    }
};

class NumArray {
private:
    int n;
    SegTree seg;
public:
    NumArray(vector<int>& nums) {
        n = nums.size( ) - 1;

        for( int i = 0; i <= n; i++ )
            seg.update(seg.root, 0, n, i, i, nums[i]);
    }

    void update(int idx, int val) {
        seg.update(seg.root, 0, n, idx, idx, val);
    }

    int sumRange(int left, int right) {
        return seg.query(seg.root, 0, n, left, right);
    }
};

signed main( ) {
    vector<int> nums = { 1, 3, 5 };
    NumArray num(nums);
    cout << num.sumRange(0, 2) << endl;
    num.update(0, 2);
    cout << num.sumRange(0, 2) << endl;
}

// 307. 区域和检索 - 数组可修改