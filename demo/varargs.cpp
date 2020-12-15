#include <iostream>
#include <utility>

// パラメータパックが空になったら終了
void print() {}

// ひとつ以上のパラメータを受け取るようにし、
// 可変引数を先頭とそれ以外に分割する
template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
  std::cout << head << std::endl;

  // パラメータパックtailをさらにheadとtailに分割する
  print(std::forward<Tail>(tail)...);
}

int main()
{
  print(1, 'a', "hello");
}
