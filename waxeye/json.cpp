#include <string.h>
#include "json_parser.h"

#include "strconv.h"
#include <variant>
#include "nameof.hpp"
#include <boost/variant.hpp>
#include <iomanip>

template <typename T>
struct tree
{
  size_t token_type;
  std::string token;
  std::vector<T> children;
  friend std::ostream &operator<<(std::ostream &stream, const tree<T> &value)
  {
    stream << "[tree]";
    return stream;
  }
};


using property_type = boost::make_recursive_variant<bool, float, double, long double,
 tree<boost::recursive_variant_>,
 std::vector<boost::recursive_variant_>,
 std::unordered_map<std::string, boost::recursive_variant_>
 >::type;

using tree_type = tree<property_type>;
using array_type = std::vector<property_type>;
using map_type = std::unordered_map<std::string, property_type>;

class printer
    : boost::static_visitor<void>
{
  std::ostream &_s;
  const std::size_t _nest_level = 0;

public:
  explicit printer(std::ostream &s, const std::size_t nest_level = 0)
      : _s(s), _nest_level(nest_level)
  {
  }

  auto indent(const std::size_t delta_nest_level = 0) const
  {
    for (std::size_t n = 0; n < _nest_level + delta_nest_level; ++n)
      _s << "  ";
  }

  auto operator()(const tree_type &o) const -> void
  {
    indent();
    _s << o.token << "[\n";
    for (auto i = o.children.cbegin(); i != o.children.cend(); ++i)
    {
      boost::apply_visitor(printer(_s, _nest_level + 1), *i);
      if (i + 1 != o.children.cend())
        _s << ",";
      _s << "\n";
    }
    indent();
    _s << "]";
  }

  auto operator()(const array_type &o) const -> void
  {
    indent();
    _s << "[\n";
    for (auto i = o.cbegin(); i != o.cend(); ++i)
    {
      boost::apply_visitor(printer(_s, _nest_level + 1), *i);
      if (i + 1 != o.cend())
        _s << ",";
      _s << "\n";
    }
    indent();
    _s << "]";
  }

  auto operator()(const map_type &o) const -> void
  {
    indent();
    _s << "{\n";
    for (auto i = o.cbegin(); i != o.cend();)
    {
      indent(1);
      _s << '"' << i->first << '"' << ":\n";
      boost::apply_visitor(printer(_s, _nest_level + 2), i->second);
      if (++i != o.cend())
        _s << ",";
      _s << "\n";
    }
    indent();
    _s << "}";
  }

  auto operator()(const bool e) const -> void
  {
    indent();
    _s << std::boolalpha << e;
  }

  template <typename T>
  auto operator()(const T e) const -> void
  {
    indent();
    _s << std::fixed << std::setprecision(std::numeric_limits<T>::max_digits10 - 2) << e;
  }
};

void variant01()
{
  // 継承関係にないクラス群
  struct A
  {
    void f() {}
  };
  struct B
  {
    void f() {}
  };
  struct C
  {
    void f() {}
  };

  // A, B, Cのいずれかの型を代入できる型
  std::variant<A, B, C> v = A{}; // A型のオブジェクトを代入
  v = B{};                       // B型のオブジェクトに切り替え

  // B型オブジェクトを保持しているか
  if (std::holds_alternative<B>(v))
  {
    // 保持しているB型オブジェクトを取得
    B &b = std::get<B>(v);
  }

  // どの型が代入されていたとしても、共通のインタフェースを呼び出す
  std::visit([](auto &x) {
    x.f();
  },
             v);
}

int main()
{
  using namespace std;

  array_type p1;
  p1.emplace_back(1.23e-4f);
  p1.emplace_back(1.23e-4);
  p1.emplace_back(1.23e-4l);
  p1.emplace_back(true);
  p1.emplace_back(p1);
  tree_type t1;
  t1.token = "TKN";
  t1.children.emplace_back(12.3);
  p1.emplace_back(t1);
  map_type p2;
  p2.emplace("fuga", p1);
  p2.emplace("piyo", false);
  p1.emplace_back(p2);
  property_type p = p1;

  boost::apply_visitor(printer(std::cout), p);
  variant01();

  // int, char, std::stringのいずれかの型の値を保持できる型
  std::variant<int, char, std::string> v = 3; // int型の値を代入

  // 候補型の0番目の型 (int) を保持しているか
  if (v.index() == 0)
  {
    int &x = std::get<0>(v); // 型のインデックスを指定して、保持している値を取得
    std::cout << "(1)" << x << std::endl;
  }

  v = std::string("Hello"); // std::string型オブジェクトを代入

  // std::string型を保持しているか
  if (std::holds_alternative<std::string>(v))
  {
    std::string &x = std::get<std::string>(v); // 型を指定して、保持している値を取得
    std::cout << "(2)" << x << std::endl;
  }

  // Create our parser
  struct parser_t *parser = json_parser_new();

  // Setup our input
  char data[] = "42";
  struct input_t *input = input_new(data, strlen(data));

  // Parse our input
  struct ast_t *ast = parse(parser, input);

  // Print our ast
  display_ast(ast, json_type_strings);

  unicode_ostream uout(cout);

  formatA(cout, "type=%d\n", ast->type);
  uout << "type=" << nameof::nameof_enum(ast->type) << std::endl;

  if (ast->type == AST_TREE)
  {
    formatA(cout, "AST_TREE\n");
    ast_tree_t *tree = ast->data.tree;
    uout << tree->type << json_type_strings[tree->type] << endl;
    uout << tree->children->size << endl;
    for (size_t i = 0; i < tree->children->size; ++i)
    {
      ast_t *child = (ast_t *)vector_get(tree->children, i);
      uout << child->type << endl;
      uout << json_type_strings[child->data.tree->type] << endl;
    }
  }

  ast_recursive_delete(ast);
  input_delete(input);
  parser_delete(parser);

  return 0;
}
