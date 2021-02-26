#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Solution {
public:
  const long MAX = 2147483648;
  bool is_digit(char ch) {
    unsigned short diff = ch - '0';
    return diff >= 0 && diff <= 9;
  }
  int digit(char ch) { return ch - '0'; }
  int myAtoi(string s) {
    auto is_digit = [](const char ch) { return ch >= '0' && ch <= '9'; };
    auto digit = [](const char ch) { return ch - '0'; };
    bool is_positive = true;
    auto it = s.cbegin();
    while (it < s.cend() && *it == ' ') ++it;
    if (it == s.cend()) return 0;
    if (*it == '-') {
      is_positive = false;
      ++it;
    }
    else if (*it == '+') {
      is_positive = true;
      ++it;
    }
    else if (!isdigit(*it)) return 0;
    long num = 0;
    while (it < s.cend() && is_digit(*it)) {
      num = 10 * num + digit(*it);
      if (is_positive && num >= MAX) return MAX - 1;
      if (!is_positive && num > MAX) return -MAX;
      ++it;
    }
    return is_positive ? num : -num;
  }
};

int main() {
  string s ="-2147483647";
  cout << Solution().myAtoi(s);
}
