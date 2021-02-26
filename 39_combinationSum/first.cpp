#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
 * target为根结点，可能的值为边，子结点为target减去边后的值
 * 递归求子树的组合
 * 去重，遍历完第一个子树后，即代表可以在后面的组合中排除掉该子树根结点所代表的值
 */
bool status[30] = {};
class Solution {
  vector<vector<int>> result;
  vector<int> record;

  void travel(vector<int>& candidates, int target, size_t begin) {
    for (size_t i = begin; i < candidates.size(); ++i) {
      int new_target = target - candidates[i];
      if (new_target < 0) break;
      if (new_target == 0) {
        record.push_back(candidates[i]);
        result.push_back(record);
        record.pop_back();
        break;
      }
      record.push_back(candidates[i]);
      travel(candidates, new_target, i);
      record.pop_back();
    }
  }
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    travel(candidates, target, 0);
    return result;
  }
};

int main() {
  
}
