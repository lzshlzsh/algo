# 字符串问题

## 最长回文字串[longest_palindrom.cpp](longest_palindrom.cpp)
原题[longest-palindromic-substring](https://leetcode-cn.com/problems/longest-palindromic-substring/)

解决方案参考[最长回文字串官方题解](https://leetcode-cn.com/problems/longest-palindromic-substring/solution/)

## 正则表达式匹配[rege_match.cpp](rege_match.cpp)
原题[regular-expression-matching](https://leetcode-cn.com/problems/regular-expression-matching/)

### 解法一：递归
- 时间复杂度`O(n*m)`
- 空间复杂度`O(n(n+m))`

### 解法二：动态规划
- 时间复杂度`O(n*m)`
- 空间复杂度`O(n*m)`

### 解法三：编译技术的词法分析器
`TODO:`

# 数组问题
## 最大面积[max_area.cpp](max_area.cpp)
原题[container-with-most-water](https://leetcode-cn.com/problems/container-with-most-water/)

### 解法：双指针法
- 时间复杂度`O(n)`
- 空间复杂度`O(1)`

证明：
`a[0..n-1]`为输入数组，则
目标函数`f = max{s(i,j) | s(i,j) = min(a[i],a[j])*(j-i), 0 <= i < j <= n-1}`。
`s(i,j)`共有`(n)(n-1)/2`种可能，暴力法时间复杂度为`O(n*n)`。

对于`s(i,j) = min(a[i],a[j])*(j-i)`:
1. 若`a[i] < a[j]`，则对于任何`k<j`都有`s(i,k) <= a[i]*(k-i) < a[i]*(j-i) = s(i,j)`，根据目标函数`f`的定义，无需计算`s(i,k), k<j`
2. 若`a[i] == a[j]`，则`s(i,k) <= a[i]*(k-i) < a[i]*(j-i) = s(i,j), k<j`，并且`s(k,j) <= a[j]*(j-k) < a[j]*(j-i) = s(i,j), k>i`，因此无需计算`s(i,k), k<j`以及`s(k,j), k>i`
3. 若`a[i] > a[j]`，则`s(k,j) <= a[j]*(j-k) < a[j]*(j-i) = s(i,j), k>i`，无需计算`s(k,j), k>i`

因此，初始化`i=0, j=n-1`，根据`a[i], a[j]`的大小，按照以下规则移动`i, j`即可得出目标函数值。
1. 若`a[i] < a[j]`则`i++`
2. 若`a[i] == a[j]`则`i++, j--`
3. 若`a[i] > a[j]`则`j--`

`i,j`的增加次数不超过`n`，时间复杂度`O(n)`
