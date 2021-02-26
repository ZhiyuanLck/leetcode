#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
 * 1: I(1), X(10), C(100), M(1000)
 * 2, 3: 2(II), 20(XX), 200(CC), 2000(MM)
 * 4: 4(IV), 40(XL), 400(CD)
 * 5: 5(V), 50(L), 500(D)
 * 6-8: 6(VI), 60(LX), 600(DC)
 * 9: 9(IX), 90(XC), 900(CM)
 */

const unordered_map<unsigned short, string> roman = {
  {1, "I"}, {10, "X"}, {100, "C"}, {1000, "M"},
  {2, "II"}, {20, "XX"}, {200, "CC"}, {2000, "MM"},
  {3, "III"}, {30, "XXX"}, {300, "CCC"}, {3000, "MMM"},
  {4, "IV"}, {40, "XL"}, {400, "CD"},
  {5, "V"}, {50, "L"}, {500, "D"},
  {6, "VI"}, {60, "LX"}, {600, "DC"},
  {7, "VII"}, {70, "LXX"}, {700, "DCC"},
  {8, "VIII"}, {80, "LXXX"}, {800, "DCCC"},
  {9, "IX"}, {90, "XC"}, {900, "CM"}
};

class Solution {
public:
  string intToRoman(int num) {
    int base;
    if (num >= 1000) base = 1000;
    else if (num >= 100) base = 100;
    else if (num >= 10) base = 10;
    else base = 1;
    string s;
    while (num) {
      // cout << num / base * base << " " << roman[num / base * base] << endl;
      unsigned int idx = num / base * base;
      if (idx) s += roman.at(num / base * base);
      num %= base;
      base /= 10;
    }
    return s;
  }
};

int main() {
  int n = 101;
  cout << Solution().intToRoman(n);
}
