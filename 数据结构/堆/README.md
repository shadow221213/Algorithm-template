<!--
 * @Description: 
 * @Author: shadow221213
 * @Date: 2023-11-01 13:56:45
 * @LastEditTime: 2023-11-21 22:00:41
-->
# <div align="center">原地堆化</div>

<!-- TOC -->

- [原地堆化](#原地堆化)
  - [代码](#代码)
  - [方法：](#方法)
  - [例题：](#例题)

<!-- /TOC -->

## 代码
> [点击此处](./原地堆化.cpp)

## 方法：
1. `make_heap(all(nums))` ：就地建堆，保证最大值在最前面，其他不确定，$O(n)$
2. `pop_heap(all(nums))` ：将堆顶元素移动到最后，并将新的最大值置于最前面
3. `push_heap(all(nums))` ：将最后元素插入堆中
            
## 例题：
*2558. 从数量最多的堆取走礼物*