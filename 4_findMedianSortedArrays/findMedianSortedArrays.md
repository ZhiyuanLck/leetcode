# 两个正序数组的中位数

设中位数为median，两个数组分别为a, b, 且长度分别为m, n

## 特判

按顺序进行特判

- 其中一个数组为空时：直接返回另一个数组的中位数
- a[m - 1] <= b[0]或a[0] >= b[n - 1]时，返回拼接数组的中位数
- 排除median只在一个数组范围内的情况
设sum = m + n - 1
m + n为偶数（sum为奇数）时，i, j为中间两个数，k1为i的索引，k2为j的索引
m + n为奇数（sum为偶数）时，i, j, k为中间三个数，k1为i的索引，k2为k的索引
  - b[0] <= median <= a[0]     <==> k1 < n  && b[k1] <= a[0]
    ==> median = even ? (b[k1] + next(b, k1)) / 2         : next(b, k1)
  - a[0] <= median <= b[0]     <==> k1 < m  && a[k1] <= b[0]
    ==> median = even ? (a[k1] + next(a, k1)) / 2         : next(a, k1)
  - a[m - 1] <= median <= b[n - 1] <==> k2 >= m && b[k2 - m] >= a[m - 1]
    ==> median = even ? (b[k2 - m] + prev(b, k2 - m)) / 2 : b[k2 - m]
  - median >= b[n - 1] <==> k2 >= n && a[k2 - n] >= b[n - 1]
    ==> median = even ? (a[k2 - n] + prev(a, k2 - n)) / 2 : a[k2 - n]

next(a, k)将a[k]的下一个值与b[0]比较，取较小值
prev(b, k)将b[k]的上一个值与a[m - 1]比较，取较大值

## 思路

假设已知a[l1] <= median <= a[r1]且b[l2] <= median <= b[r2]
其中0 <= l1 < r1 <= m, 0 <= l2 < r2 <= n,
且l1 <= mid1 < r1, l2 <= mid2 < r2使得mid1 + mid2 + 2 = [(m + n) / 2]

设d = [min(r1 - l1, r2 - l2) / 2]

1. 当a[mid1] = b[mid2]时，median = a[mid1]

2. 当a[mid1] > b[mid2]时，b[mid2] <= median <= a[mid1]
即a[l1] <= median <= a[mid1], b[mid2] <= median <= b[r2 - 1]
r1 = mid1, l2 = mid2, “左移”mid1，“右移”mid2，移动距离为d

3. 当a[mid1] < b[mid2]时，a[mid1] <= median <= b[mid2]
即a[mid1] <= median <= a[r1], b[l2] <= median <= b[mid2]
l1 = mid1, l2 = mid2, “左移”mid1，“右移”mid2，移动距离为d

### 初始条件

排除特判后，一定有a[0] <= median <= a[m - 1]且b[0] <= median <= b[n - 1]
即可令l1 = 0, r1 = m - 1, l2 = 0, r2 = n - 1
设左半部分的总数为total = even ? (m + n) / 2 + 1 : (m + n + 1) / 2;
和mid1 = [(m - 1) / 2], mid2 = total - 2 - mid1

### 终止条件

mid1, mid2分隔的左半边部分都小于等于右半部分
