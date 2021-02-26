#include <iostream>
#include <vector>
#include <string>


using namespace std;

const int MAX = 2147483647;
const int MIN = -2147483648;

class Solution {
public:
  int divide(int dividend, int divisor) {
    if (dividend == 0) return 0; // 被除数为0
    if (dividend == -2147483648 && divisor == -1) return 2147483647; // 溢出
    if (divisor == 1) return dividend;
    if (divisor == -1) return -dividend;
    bool is_positive = false;
    if (dividend > 0 && divisor > 0) is_positive = true;
    else if (dividend < 0 && divisor < 0) is_positive = true;
    // 转换为负数，否则可能溢出
    if (dividend > 0) dividend = -dividend;
    if (divisor > 0) divisor = -divisor;
    if (dividend > divisor) return 0; // 商绝对值小于1
    int sum = 0;
    while (dividend <= divisor) { // 对每部分进行二分
      int n = is_positive ? 1 : -1;
      int b = divisor;
      while (dividend - b <= b) { // 写成dividend <= b + b会溢出
        b += b;
        n += n;
      }
      dividend -= b;
      sum += n;
    }
    return sum;
  }
};

int main() {
  cout << Solution().divide(10, -3);
}
