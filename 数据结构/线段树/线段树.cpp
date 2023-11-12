/*
 * @Description:
 * @Author: shadow221213
 * @Date: 2023-10-09 19:31:02
 * @LastEditTime: 2023-11-12 17:57:19
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 1e4;
const int M = 1e9;

template <class T> class cache {
protected:
    T *next;
private:
    static T *head;
    static const size_t SIZE;
    static void add(T *p) {
        p->cache<T>::next = head;
        head = p;
    }
public:
    void *operator new(size_t s) {
        if( !head ) {
            T *a = new T[SIZE];
            for( size_t i = 0; i < SIZE; i++ )
                add(a + i);
        }
        T *p = head;
        head = head->cache<T>::next;
        return p;
    }
    void operator delete(void *p, size_t) {
        if( p ) add(static_cast< T * >(p));
    }
    virtual ~cache( ) { }
};
template <class T> T *cache<T>::head = 0;
template <class T> const size_t cache<T>::SIZE = N;
class node: public cache<node> {
public:
    node *l;
    node *r;
    int val;
    int lazy;
};

class SegTree {
private:
    int maxN;
    node *root; // 需要外部调用根节点
public:
    SegTree(int n = M) {
        maxN = n;
        root = new node( );
    }
    void pushUp(node *root) {
        root->val = root->l->val + root->r->val;
    }
    void pushDown(node *root, int l, int r) {
        if( root->l == nullptr ) root->l = new node( );
        if( root->r == nullptr ) root->r = new node( );

        if( root->lazy == 0 ) return;

        int mid = l + r >> 1;
        root->l->val += root->lazy * (mid - l + 1);
        root->r->val += root->lazy * (r - mid);
        // 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
        root->l->lazy += root->lazy;
        root->r->lazy += root->lazy;
        root->lazy = 0;
    }
    void add(int l, int r, int val = 1) {
        update(root, 1, M, l, r, val);
    }
    void remove(int l, int r, int val = -1) {
        update(root, 1, M, l, r, val);
    }
    void update(node *root, int start, int end, int &l, int &r, int val) {
        if( l <= start && end <= r ) {
            // 在此处修改区间[l, r]的值
            root->val = val * (end - start + 1);
            root->lazy = val;
            return;
        }

        pushDown(root, start, end);
        int mid = start + end >> 1;

        if( l <= mid ) update(root->l, start, mid, l, r, val);
        if( r > mid ) update(root->r, mid + 1, end, l, r, val);

        pushUp(root);
    }
    int query(int l, int r) {
        return query(root, 1, M, l, r);
    }
    int query(node *root, int start, int end, int &l, int &r) {
        if( l <= start && end <= r ) return root->val;

        pushDown(root, start, end);
        int mid = start + end >> 1, ans = 0;

        if( l <= mid ) ans = query(root->l, start, mid, l, r);
        if( r > mid ) ans += query(root->r, mid + 1, end, l, r);

        return ans;
    }
};

class NumArray {
private:
    SegTree *seg;
public:
    NumArray(vector<int> &nums) {
        int n = nums.size( ) - 1;
        seg = new SegTree(n + 1);

        for( int i = 0; i <= n; i++ )
            seg->add(i, i, nums[i]);
    }

    void update(int idx, int val) {
        seg->add(idx, idx, val);
    }

    int sumRange(int left, int right) {
        return seg->query(left, right);
    }
};

signed main( ) {
    vector<int> nums = { 1, 3, 5 };
    NumArray num(nums);
    cout << num.sumRange(0, 2) << endl;
    num.update(0, 2);
    cout << num.sumRange(0, 2) << endl;
}