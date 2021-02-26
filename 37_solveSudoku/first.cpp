#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// template<template<class, class...> class T, class H, class... Args>
// ostream& operator<<(ostream &os, const T<H, Args...> &obj) {
    // bool start = true;
    // for (auto v: obj) {
        // if (start) {
            // os << v;
            // start = false;
        // }
        // else {
            // os << ' ' << v;
        // }
    // }
    // os << '\n';
    // return os;
// }

/*
 * 转换求解0-1数组
 * 数组有81 * 9行代表所有的解，有81 * 4代表满足的条件
 * [0, 81) 在(i, j)落子，0 <= i, j <= 8
 * [81, 162) 在i行使用了n
 * [162, 243) 在j列使用了n
 * [243, 324) 在i / 3 * 3 + j / 3块使用了n
 * DancingLink 进行求解和回溯
 */

using Int = unsigned short;

class MetaNode {
public:
  Int row, col, num;
  vector<vector<char>>& board;
  MetaNode(vector<vector<char>>& board, Int row, Int col, Int num) :
    board(board), row(row), col(col), num(num) {}
  void choose() {
    cout << "(" << row << ", " << col << ") = " << num << endl;
    board[row][col] = char('0' + num);
  }
};

class Node {
public:
  shared_ptr<MetaNode> info;
  shared_ptr<Node> head;
  shared_ptr<Node> next;
  shared_ptr<Node> prev;
  shared_ptr<Node> above;
  shared_ptr<Node> below;
  void init(shared_ptr<Node> self) {
    next = self;
    prev = self;
    above = self;
    below = self;
  }
  void choose() { info->choose(); }
};

class DancingLink {
  vector<vector<char>>& board;
  vector<shared_ptr<Node>> record;
  shared_ptr<Node> head;
  vector<shared_ptr<Node>> col_heads;
public:
  DancingLink(vector<vector<char>>& board);
  void choose(shared_ptr<Node> pick);
  shared_ptr<Node> withdraw();
  void create_row(Int row, Int col, Int num);
  bool empty() {
    if (head->next == head) return true;
    auto ptr = head->next;
    while (ptr != head) {
      if (ptr->below != ptr) return false;
      ptr = ptr->next;
    }
    return true;
  }
  shared_ptr<Node> next() {
    auto ptr = head->next;
    while (ptr != head) {
      if (ptr->below != ptr) break;
      ptr = ptr->next;
    }
    return ptr->below;
  }
  void show() {
    vector<vector<Int>> a;
    for (int i = 0; i < 9; ++i) {
      vector<Int> b(9, 0);
      a.push_back(b);
    }
    for (int i = 0; i < record.size(); ++i) {
      auto info = record[i]->info;
      a[info->row][info->col] = info->num;
    }
    // if (a[0][2] == 1) return;
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        cout << a[i][j] << (j == 8 ? "" : " ");
      }
      cout << "\n";
    }
  }
};

DancingLink::DancingLink(vector<vector<char>>& board) : board(board) {
  // init head
  head = make_shared<Node>();
  head->init(head);
  for (size_t i = 0; i < 324; ++i) {
    auto h = make_shared<Node>();
    head->prev->next = h;
    h->prev = head->prev;
    head->prev = h;
    h->next = head;
    h->above = h;
    h->below = h;
    h->head = h;
    col_heads.push_back(h);
  }
  // 建立链表
  for (size_t i = 0; i < 9; ++i) {
    for (size_t j = 0; j < 9; ++j) {
      char cur = board[i][j];
      if (cur == '.') {
        for (size_t n = 1; n < 10; ++n) {
          create_row(i, j, n);
        }
      }
      else {
        create_row(i, j, cur - '0');
      }
    }
  }

  // solve
  int i = 0;
  while (record.size() < 81) {
    // if (++i == 1000) break;
    cout << "size " << record.size() << endl;
    if (head->next->below == head->next) {
      shared_ptr<Node> pick;
      // 可能的原因：回溯前进到head后继续回退
      do {
        cout << "withdraw\n";
        pick = withdraw();
        if (pick == nullptr) {
          cout << "NO ANSWER!\n";
          return;
        }
      } while (pick == pick->head);
      choose(pick);
      continue;
    }
    choose(head->next->below);
    show();
  }
}

void DancingLink::choose(shared_ptr<Node> pick) {
  // 求解
  record.push_back(pick);
  pick->choose();
  // 遍历选择的行中的结点，不需要管当前列
  auto row_ptr = pick;
  do {
    // 排除满足相同条件的行
    for (auto col_ptr = row_ptr->below; col_ptr != row_ptr; col_ptr = col_ptr->below) {
      if (col_ptr == col_ptr->head) { // 头结点特殊处理
        col_ptr->prev->next = col_ptr->next;
        col_ptr->next->prev = col_ptr->prev;
        continue;
      }
      // 摘出该行，ptr遍历该行结点
      for (auto ptr = col_ptr->next; ptr != col_ptr; ptr = ptr->next) {
        ptr->above->below = ptr->below;
        ptr->below->above = ptr->above;
      }
    }
    row_ptr = row_ptr->next;
  } while (row_ptr != pick);
}

shared_ptr<Node> DancingLink::withdraw() {
  if (record.empty()) return nullptr;
  // 回溯
  auto pick = record.back();
  record.pop_back();
  auto row_ptr = pick->prev;
  do {
    // 回溯满足相同条件的行
    for (auto col_ptr = row_ptr->above; col_ptr != row_ptr; col_ptr = col_ptr->above) {
      if (col_ptr == col_ptr->head) { // 跳过列的头结点
        col_ptr->prev->next = col_ptr;
        col_ptr->next->prev = col_ptr;
        continue;
      }
      for (auto ptr = col_ptr->prev; ptr != col_ptr; ptr = ptr->prev) {
        ptr->above->below = ptr;
        ptr->below->above = ptr;
      }
    }
    row_ptr = row_ptr->prev;
  } while (row_ptr != pick->prev);
  return pick->below;
}

void DancingLink::create_row(Int row, Int col, Int num) {
  auto info = make_shared<MetaNode>(board, row, col, num);
  vector<Int> idx;
  idx.push_back(row * 9 + col); // (row, col)
  idx.push_back(80 + row * 9 + num); // row行选择num
  idx.push_back(161 + col * 9 + num); // col列选择num
  idx.push_back(242 + (row / 3 * 3 + col / 3) * 9 + num); // row / 3 * 3 + col / 3块选择num
  auto h = make_shared<Node>();
  h->next = h;
  h->prev = h;
  for (auto const& i : idx) {
    auto node = make_shared<Node>();
    // 插入行中
    node->info = info;
    h->prev->next = node;
    node->prev = h->prev;
    node->next = h;
    h->prev = node;
    // 插入列中
    auto col_h = col_heads[i];
    col_h->above->below = node;
    node->above = col_h->above;
    node->below = col_h;
    col_h->above = node;
    // 记录列头节点
    node->head = col_heads[i];
  }
  // 移除h
  h->prev->next = h->next;
  h->next->prev = h->prev;
  h->prev.reset();
  h->next.reset();
}

class Solution {
public:
  void solveSudoku(vector<vector<char>>& board) {
    DancingLink a(board);
  }
};

int main() {
  vector<vector<char>> board = {
  {'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}
  };
  Solution().solveSudoku(board);
}
