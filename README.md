# 编译环境配置
```
git subtree pull -P .Makefile https://github.com/lzshlzsh/Makefile.git master --squash
```
# 递归和动态规划
## 最长单调上升子序列算法[max_nodec.cpp](max_nodec.cpp)
设`A[N]`为`N`个整数的数组，求最长单调上升子序列，解可以有多个，输出一个即可。
例如`3 2 8 6 7 4 5 7 3`，最长单调上升子序列的长度为4。
解：`2 4 5 7`

### 解法
- 时间复杂度: `O(nlog(n))`
- 空间复杂度: `O(n)`

假设`f(i)`为以`A[i]`结尾的最长单调上升子序列的长度，那么
1. `f(i) = 1`，当`i == 0`
2. `f(i) = max{f(j) + 1| j < i, A[j] <= A[i]}`   --- (式1)
3. 所求最长单调上升子序列的长度为`max{f(i)}`

每次计算`f(i)`按照(式1)遍历`A[0..i-1]`计算，整个算法时间复杂度为`O(n*n)`。我们注意到，对于`j, k`满足`j < i，k < i, f(k) <= f(j)`，如果`A[k] > A[j]`，那么`A[k]和f(k)`是没有必要的。因为如果`A[i] >= A[k] > A[j]`，那么`f(i) >= f(j) + 1 >= f(k) + 1`。因此，我们只需保存`f(i_1) < f(i_2) < ... < f(i_t)`，满足`A[i_1] <= A[i_2] <= ... <= A[i_t], f(i_j) = f(i_j-1) + 1`。按(式1)计算`f(i)`时，找到第一个`A[j]`满足`A[j] > A[i]`，`f(i) = f(j)`，并替换`f(j)`为`f(i)`。如果没有找到这样的j，那么`f(i) = f(i_t) + 1`。很显然，每次(式1)计算的时间复杂度不超过为`O(log(n))`，总的时间复杂度：`O(nlog(n))`。

## 最长公共子序列[longest_common_subseq.cpp](longest_common_subseq.cpp)
求两个字符串`S[0..m-1]`和`T[0..n-1]`的最长公共子序列。
例如`S=dgebbf, T=egefcb`，其最长公共子序列为`ge`。

### 解法
- 时间复杂度：`O(n*m)`
- 空间复杂度：`O(n*m)`

设`f(i,j)`为`S[0..i-1]`和`T[0..j-1]`的最长公共子序列的长度。那么：
1. `f(i,j) = 0`当`i == 0`或者`j == 0`
2. `f(i,j) = f(i-1,j-1) + 1`当`S[i-1] == T[j-1]`
3. `f(i,j) = max(f(i,j-1), f(i-1,j))`当`S[i-1] != T[j-1]`

## 最长公共子串[longest_common_substr.cpp](longest_common_substr.cpp)

求两个字符串`S[0..m-1]`和`T[0..n-1]`的最长公共子串。
例如`S=abchg, T=bcjdg`，其最长公共子序列为`bcg`。

### 解法一
- 时间复杂度：`O(n*m)`
- 空间复杂度：`O(n*m)`

设`f(i,j)`为`S[i-1] == T[j-1]`结尾的最长公共子串的长度。那么：
1. `f(i,j) = 0`当`i == 0`或者`j == 0`
2. `f(i,j) = f(i-1,j-1) + 1`当`S[i-1] == T[j-1]`
3. `f(i,j) = 0`当`S[i-1] != T[j-1]`

### 解法二
- 时间复杂度：
- 空间复杂度：

# 字符串问题

## KMP算法 [kmp_01.cpp](kmp_01.cpp)
在`A[0..n-1]`中查找字串`P[0..m-1]`所有出现的位置`k`，使得
`A[k..m-1+k] = P[0..m-1]`

## 解法
- 时间复杂度：`O(m+n)`
- 空间复杂度：`O(m)`

前缀函数`f: {0,1,...,m-1} -> {-1,0,...,m-2}, f(i) = max{k | k < i, P[0..k]为P[0..i]的后缀}`，前缀函数计算算法：

```
f(0..m-1) = -1
j = -1
for i in [1, m-1]:
  while j >= 0 and P[j+1] != P[i]:
    j = f(j)
  if P[j+1] == P[i]:
    j++
  f(i) = j
```

搜索算法：

```
j = -1
for i in [0, n-1]:
  while j >= 0 and P[j+1] != A[i]:
    j = f(j)
  if A[j+1] == A[i]:
    j++
  if j == m-1:
    print "find P at i-m+1"
    j = f(j)
```
