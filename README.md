# 编译环境配置
```
git subtree pull -P .Makefile https://github.com/lzshlzsh/Makefile.git master --squash
```
# 递归和动态规划
## 最长单调上升子序列算法[max_nodec.cpp](max_nodec.cpp)
- 时间复杂度: `O(nlog(n))`
- 空间复杂度: `O(n)`

### 问题描述
设`A[N]`为`N`个整数的数组，求最长单调上升子序列，解可以有多个，输出一个即可。
例如`3 2 8 6 7 4 5 7 3`，最长单调上升子序列的长度为4。
解：`2 4 5 7`

### 解法
假设f为所求，那么
`TODO:`

# 字符串问题

## KMP算法 [kmp_01.cpp](kmp_01.cpp)

## 问题描述
在`A[0..n-1]`中查找字串`P[0..m-1]`所有出现的位置`k`，使得
`A[k..m-1+k] = P[0..m-1]`

## 解法
前缀函数`f: {0,1,...,m-1} -> {-1,0,...,m-2}, f(i) = max{k | k < i, P[0..k]为P[0..i]的后缀}`


