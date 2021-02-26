#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <unordered_map>


using namespace std;

// <i, j> : <(i + j) % 10, (i + j) / 10
const unordered_map<pair<char, char>, pair<char, char>> ADD = {
  {make_pair('1', '1'), make_pair('2', '0')},
  {make_pair('1', '2'), make_pair('3', '0')},
  {make_pair('1', '3'), make_pair('4', '0')},
  {make_pair('1', '4'), make_pair('5', '0')},
  {make_pair('1', '5'), make_pair('6', '0')},
  {make_pair('1', '6'), make_pair('7', '0')},
  {make_pair('1', '7'), make_pair('8', '0')},
  {make_pair('1', '8'), make_pair('9', '0')},
  {make_pair('1', '9'), make_pair('0', '1')},
  {make_pair('2', '1'), make_pair('3', '0')},
  {make_pair('2', '2'), make_pair('4', '0')},
  {make_pair('2', '3'), make_pair('5', '0')},
  {make_pair('2', '4'), make_pair('6', '0')},
  {make_pair('2', '5'), make_pair('7', '0')},
  {make_pair('2', '6'), make_pair('8', '0')},
  {make_pair('2', '7'), make_pair('9', '0')},
  {make_pair('2', '8'), make_pair('0', '1')},
  {make_pair('2', '9'), make_pair('1', '1')},
  {make_pair('3', '1'), make_pair('4', '0')},
  {make_pair('3', '2'), make_pair('5', '0')},
  {make_pair('3', '3'), make_pair('6', '0')},
  {make_pair('3', '4'), make_pair('7', '0')},
  {make_pair('3', '5'), make_pair('8', '0')},
  {make_pair('3', '6'), make_pair('9', '0')},
  {make_pair('3', '7'), make_pair('0', '1')},
  {make_pair('3', '8'), make_pair('1', '1')},
  {make_pair('3', '9'), make_pair('2', '1')},
  {make_pair('4', '1'), make_pair('5', '0')},
  {make_pair('4', '2'), make_pair('6', '0')},
  {make_pair('4', '3'), make_pair('7', '0')},
  {make_pair('4', '4'), make_pair('8', '0')},
  {make_pair('4', '5'), make_pair('9', '0')},
  {make_pair('4', '6'), make_pair('0', '1')},
  {make_pair('4', '7'), make_pair('1', '1')},
  {make_pair('4', '8'), make_pair('2', '1')},
  {make_pair('4', '9'), make_pair('3', '1')},
  {make_pair('5', '1'), make_pair('6', '0')},
  {make_pair('5', '2'), make_pair('7', '0')},
  {make_pair('5', '3'), make_pair('8', '0')},
  {make_pair('5', '4'), make_pair('9', '0')},
  {make_pair('5', '5'), make_pair('0', '1')},
  {make_pair('5', '6'), make_pair('1', '1')},
  {make_pair('5', '7'), make_pair('2', '1')},
  {make_pair('5', '8'), make_pair('3', '1')},
  {make_pair('5', '9'), make_pair('4', '1')},
  {make_pair('6', '1'), make_pair('7', '0')},
  {make_pair('6', '2'), make_pair('8', '0')},
  {make_pair('6', '3'), make_pair('9', '0')},
  {make_pair('6', '4'), make_pair('0', '1')},
  {make_pair('6', '5'), make_pair('1', '1')},
  {make_pair('6', '6'), make_pair('2', '1')},
  {make_pair('6', '7'), make_pair('3', '1')},
  {make_pair('6', '8'), make_pair('4', '1')},
  {make_pair('6', '9'), make_pair('5', '1')},
  {make_pair('7', '1'), make_pair('8', '0')},
  {make_pair('7', '2'), make_pair('9', '0')},
  {make_pair('7', '3'), make_pair('0', '1')},
  {make_pair('7', '4'), make_pair('1', '1')},
  {make_pair('7', '5'), make_pair('2', '1')},
  {make_pair('7', '6'), make_pair('3', '1')},
  {make_pair('7', '7'), make_pair('4', '1')},
  {make_pair('7', '8'), make_pair('5', '1')},
  {make_pair('7', '9'), make_pair('6', '1')},
  {make_pair('8', '1'), make_pair('9', '0')},
  {make_pair('8', '2'), make_pair('0', '1')},
  {make_pair('8', '3'), make_pair('1', '1')},
  {make_pair('8', '4'), make_pair('2', '1')},
  {make_pair('8', '5'), make_pair('3', '1')},
  {make_pair('8', '6'), make_pair('4', '1')},
  {make_pair('8', '7'), make_pair('5', '1')},
  {make_pair('8', '8'), make_pair('6', '1')},
  {make_pair('8', '9'), make_pair('7', '1')},
  {make_pair('9', '1'), make_pair('0', '1')},
  {make_pair('9', '2'), make_pair('1', '1')},
  {make_pair('9', '3'), make_pair('2', '1')},
  {make_pair('9', '4'), make_pair('3', '1')},
  {make_pair('9', '5'), make_pair('4', '1')},
  {make_pair('9', '6'), make_pair('5', '1')},
  {make_pair('9', '7'), make_pair('6', '1')},
  {make_pair('9', '8'), make_pair('7', '1')},
  {make_pair('9', '9'), make_pair('8', '1')},
};
// <i, j> : <(i * j) % 10, (i * j) / 10
const unordered_map<pair<char, char>, pair<char, char>> MUL = {
  {make_pair('1', '1'), make_pair('1', '0')},
  {make_pair('1', '2'), make_pair('2', '0')},
  {make_pair('1', '3'), make_pair('3', '0')},
  {make_pair('1', '4'), make_pair('4', '0')},
  {make_pair('1', '5'), make_pair('5', '0')},
  {make_pair('1', '6'), make_pair('6', '0')},
  {make_pair('1', '7'), make_pair('7', '0')},
  {make_pair('1', '8'), make_pair('8', '0')},
  {make_pair('1', '9'), make_pair('9', '0')},
  {make_pair('2', '1'), make_pair('2', '0')},
  {make_pair('2', '2'), make_pair('4', '0')},
  {make_pair('2', '3'), make_pair('6', '0')},
  {make_pair('2', '4'), make_pair('8', '0')},
  {make_pair('2', '5'), make_pair('0', '1')},
  {make_pair('2', '6'), make_pair('2', '1')},
  {make_pair('2', '7'), make_pair('4', '1')},
  {make_pair('2', '8'), make_pair('6', '1')},
  {make_pair('2', '9'), make_pair('8', '1')},
  {make_pair('3', '1'), make_pair('3', '0')},
  {make_pair('3', '2'), make_pair('6', '0')},
  {make_pair('3', '3'), make_pair('9', '0')},
  {make_pair('3', '4'), make_pair('2', '1')},
  {make_pair('3', '5'), make_pair('5', '1')},
  {make_pair('3', '6'), make_pair('8', '1')},
  {make_pair('3', '7'), make_pair('1', '2')},
  {make_pair('3', '8'), make_pair('4', '2')},
  {make_pair('3', '9'), make_pair('7', '2')},
  {make_pair('4', '1'), make_pair('4', '0')},
  {make_pair('4', '2'), make_pair('8', '0')},
  {make_pair('4', '3'), make_pair('2', '1')},
  {make_pair('4', '4'), make_pair('6', '1')},
  {make_pair('4', '5'), make_pair('0', '2')},
  {make_pair('4', '6'), make_pair('4', '2')},
  {make_pair('4', '7'), make_pair('8', '2')},
  {make_pair('4', '8'), make_pair('2', '3')},
  {make_pair('4', '9'), make_pair('6', '3')},
  {make_pair('5', '1'), make_pair('5', '0')},
  {make_pair('5', '2'), make_pair('0', '1')},
  {make_pair('5', '3'), make_pair('5', '1')},
  {make_pair('5', '4'), make_pair('0', '2')},
  {make_pair('5', '5'), make_pair('5', '2')},
  {make_pair('5', '6'), make_pair('0', '3')},
  {make_pair('5', '7'), make_pair('5', '3')},
  {make_pair('5', '8'), make_pair('0', '4')},
  {make_pair('5', '9'), make_pair('5', '4')},
  {make_pair('6', '1'), make_pair('6', '0')},
  {make_pair('6', '2'), make_pair('2', '1')},
  {make_pair('6', '3'), make_pair('8', '1')},
  {make_pair('6', '4'), make_pair('4', '2')},
  {make_pair('6', '5'), make_pair('0', '3')},
  {make_pair('6', '6'), make_pair('6', '3')},
  {make_pair('6', '7'), make_pair('2', '4')},
  {make_pair('6', '8'), make_pair('8', '4')},
  {make_pair('6', '9'), make_pair('4', '5')},
  {make_pair('7', '1'), make_pair('7', '0')},
  {make_pair('7', '2'), make_pair('4', '1')},
  {make_pair('7', '3'), make_pair('1', '2')},
  {make_pair('7', '4'), make_pair('8', '2')},
  {make_pair('7', '5'), make_pair('5', '3')},
  {make_pair('7', '6'), make_pair('2', '4')},
  {make_pair('7', '7'), make_pair('9', '4')},
  {make_pair('7', '8'), make_pair('6', '5')},
  {make_pair('7', '9'), make_pair('3', '6')},
  {make_pair('8', '1'), make_pair('8', '0')},
  {make_pair('8', '2'), make_pair('6', '1')},
  {make_pair('8', '3'), make_pair('4', '2')},
  {make_pair('8', '4'), make_pair('2', '3')},
  {make_pair('8', '5'), make_pair('0', '4')},
  {make_pair('8', '6'), make_pair('8', '4')},
  {make_pair('8', '7'), make_pair('6', '5')},
  {make_pair('8', '8'), make_pair('4', '6')},
  {make_pair('8', '9'), make_pair('2', '7')},
  {make_pair('9', '1'), make_pair('9', '0')},
  {make_pair('9', '2'), make_pair('8', '1')},
  {make_pair('9', '3'), make_pair('7', '2')},
  {make_pair('9', '4'), make_pair('6', '3')},
  {make_pair('9', '5'), make_pair('5', '4')},
  {make_pair('9', '6'), make_pair('4', '5')},
  {make_pair('9', '7'), make_pair('3', '6')},
  {make_pair('9', '8'), make_pair('2', '7')},
  {make_pair('9', '9'), make_pair('1', '8')},
};

class Solution {
  // pair<char, char> add(char ch1, char ch2) { return ADD[{ch1, ch2}]; }
public:
  string multiply(string num1, string num2) {

  }
};

int main() {
  // auto a = ADD[make_pair('1', '2')];
  // cout << a.first;
}
