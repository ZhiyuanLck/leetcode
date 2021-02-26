#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <unordered_map>

using namespace std;


class Solution {
  int c2i(char ch) { return int(ch - '0'); }
  int add(char n1, char n2) { return c2i(n1) + c2i(n2); }
  int mul(char n1, char n2) { return c2i(n1) * c2i(n2); }
  void app(string& r, int n) { r.push_back(char(n + '0')); }
  string add(string& num1, string& num2) {
    if (num1.empty()) return num2;
    if (num2.empty()) return num1;
    string r;
    int extra = 0, sum = 0;
    auto it1 = num1.begin(), it2 = num2.begin();
    while (it1 != num1.end() && it2 != num2.end()) {
      sum = extra + add(*it1, *it2);
      app(r, sum > 9 ? sum - 10 : sum);
      extra = sum > 9 ? 1 : 0;
      ++it1;
      ++it2;
    }
    while (it1 != num1.end()) {
      sum = extra + c2i(*it1);
      app(r, sum > 9 ? sum - 10 : sum);
      extra = sum > 9 ? 1 : 0;
      ++it1;
    }
    while (it2 != num2.end()) {
      sum = extra + c2i(*it2);
      app(r, sum > 9 ? sum - 10 : sum);
      extra = sum > 9 ? 1 : 0;
      ++it2;
    }
    if (extra) app(r, 1);
    return r;
  }
  string mul(string& num, char ch) {
    string r;
    int n = c2i(ch);
    int extra = 0, sum = 0;
    for (auto x : num) {
      sum = mul(x, ch) + extra;
      app(r, sum % 10);
      extra = sum / 10;
    }
    if (extra) app(r, extra);
    return r;
  }
public:
  string multiply(string num1, string num2) {
    if (num1.front() == '0' || num2.front() == '0') return "0";
    reverse(num1.begin(), num1.end());
    string extra, sum;
    for (auto it = num2.rbegin(); it != num2.rend(); ++it) {
      if (*it != '0') {
        auto r = extra + mul(num1, *it);
        sum = add(sum, r);
      }
      extra.push_back('0');
    }
    reverse(sum.begin(), sum.end());
    return sum;
  }
};

int main() {
  string a = "123456789";
  string b = "987654321";
  cout << Solution().multiply(a, b) << endl;
}
