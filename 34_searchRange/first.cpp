#include <iostream>
#include <vector>
#include <string>

using namespace std;


/* 特判size = 0
 * 特判a[0] > target, a[n - 1] < target
 * 左边界i
 *  - a[0] = target
 *  - i != 0, a[i - 1] < a[i] = target
 * [l, r] = [1, r]当l <= r时循环，
 * 1. a[mid - 1] < a[mid] = target时找到值
 * 2. a[mid] < target, target在[mid + 1, r]
 * 3. 否则target在[l, mid - 1]
 * 右边界i
 *  - a[n - 1] = target
 *  - i != r, target = a[i] < a[i + 1]
 * [l, r] = [l, n - 2]当l <= r时循环，
 * 1. target = a[mid] < a[mid + 1]时找到值
 * 2. a[mid] > target, target在[l, mid - 1]
 * 3. 否则target在[mid + 1, r]
 */
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.empty() || nums.front() > target || nums.back() < target) return {-1, -1};
    size_t l, r, mid;
    int left, right;
    // 搜索左边界
    if (nums.front() == target) left = 0;
    else {
      l = 1, r = nums.size() - 1;
      while (l <= r) {
        mid = (l + r) / 2;
        if (nums[mid - 1] != target && nums[mid] == target) {
          left = mid;
          break;
        }
        else if (nums[mid - 1] >= target) r = mid - 1;
        else l = mid + 1;
      }
      if (l > r) return {-1, -1};
    }
    // 搜索右边界
    if (nums.back() == target) right = nums.size() - 1;
    else {
      l = left, r = nums.size() - 2;
      while (l <= r) {
        mid = (l + r) / 2;
        if (nums[mid + 1] != target && nums[mid] == target)
        {
          right = mid;
          break;
        }
        else if (nums[mid + 1] <= target) l = mid + 1;
        else r = mid - 1;
      }
      if (l > r) return {-1, -1};
    }
    return {left, right};
  }
};

int main() {
  vector<int> nums = {5, 7, 7, 8, 8, 10};
  auto a = Solution().searchRange(nums, 8);
  cout << a[0] << " " << a[1];
}
