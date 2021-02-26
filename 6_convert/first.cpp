#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 1. a[0][i] = 2(n - 1)i
// i is odd: a[k][i] = a[k][i - 1] + 2(n - k - 1)
// i is even: a[k][i] = a[k][i - 1] + 2k
// n. a[n - 1][i] = (n - 1)(2i + 1)
class Solution {
public:
    string convert(string s, int numRows) {
      if (s.empty() || numRows == 1) return s;
      string r = "";
      for (int i = 0; 2 * (numRows - 1) * i < s.size(); ++i)
        r.push_back(s[2 * (numRows - 1) * i]);
      for (int k = 1; k < numRows - 1; ++k) {
        for (int idx = 0, i = 0;; ++i) {
          if (i == 0) idx = k;
          else idx += i & 1 ? 2 * (numRows - k - 1) : 2 * k;
          if (idx < s.size()) r.push_back(s[idx]);
          else break;
        }
      }
      for (int i = 0; (numRows - 1) * (2  * i + 1) < s.size(); ++i)
        r.push_back(s[(numRows - 1) * (2 * i + 1)]);
      return r;
    }
};

int main() {
  string s = "PAYPALISHIRING";
  s = "a";
  cout << Solution().convert(s, 1);
}
