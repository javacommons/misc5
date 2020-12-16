#include <windows.h>
#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <map>

using atom = std::variant<int, char, std::string, void *>;
using list = std::vector<atom>;
using dictionary = std::map<std::string, atom>;
using variable = std::variant<int, char, std::string, void *, list, dictionary>;
using variableList = std::vector<variable>;

#include <iostream>
#include <utility>

// パラメータパックが空になったら終了
void print(variableList &vars) {
  std::cout << vars.size() << std::endl;
}

// ひとつ以上のパラメータを受け取るようにし、
// 可変引数を先頭とそれ以外に分割する
template <class Head, class... Tail>
void print(variableList &vars, Head&& head, Tail&&... tail)
{
  std::cout << head << std::endl;
  vars.push_back(head);

  // パラメータパックtailをさらにheadとtailに分割する
  print(vars, std::forward<Tail>(tail)...);
}

int main()
{
  variableList vars;
  print(vars, 1, 'a', "hello");
  std::cout << vars.size() << std::endl;
}
