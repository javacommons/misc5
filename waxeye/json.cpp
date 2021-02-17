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
  std::string name;
  std::vector<T> children;
  explicit tree(const std::string &name, const std::string &text = "") : name(name), text(text) {}
  std::string text;
  friend std::ostream &operator<<(std::ostream &stream, const tree<T> &value)
  {
    stream << "[tree]";
    return stream;
  }
};

using property_type = boost::make_recursive_variant<bool, float, double, long double,
                                                    tree<boost::recursive_variant_>,
                                                    std::vector<boost::recursive_variant_>,
                                                    std::unordered_map<std::string, boost::recursive_variant_>>::type;

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
    _s << o.name;
    if (!o.text.empty())
      _s << '(' << o.text << ')';
    if (o.children.size() > 0)
    {
      _s << "[\n";
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
  }

  auto
  operator()(const array_type &o) const -> void
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

property_type conv_ast(ast_t *ast);

property_type conv_tree(ast_t *ast)
{
    assert(ast->type == AST_TREE);
    ast_tree_t *tree = ast->data.tree;
    tree_type result(json_type_strings[tree->type]);
    for (size_t i = 0; i < tree->children->size; ++i)
    {
      ast_t *child = (ast_t *)vector_get(tree->children, i);
      if(child->type==AST_CHAR)
      {
          result.text.push_back(child->data.c);
          continue;
      }
      result.children.emplace_back(conv_ast(child));
    }
    return result;
}

property_type conv_ast(ast_t *ast)
{
  switch (ast->type) {
  case AST_CHAR:
      break;
  case AST_EMPTY:
      break;
  case AST_ERROR:
      break;
  case AST_TREE:
      return conv_tree(ast);
  default:
      break;
  }
  tree_type t("dummy");
  return t;
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
  tree_type t1("TKN");
  tree_type k1("Number", "12.3");
  t1.children.emplace_back(k1);
  p1.emplace_back(t1);
  map_type p2;
  p2.emplace("fuga", p1);
  p2.emplace("piyo", false);
  p1.emplace_back(p2);
  property_type p = p1;

  boost::apply_visitor(printer(std::cout), p);

  // Create our parser
  struct parser_t *parser = json_parser_new();

  // Setup our input
  char data[] = R"(
{
    "glossary": {
        "title": "example glossary",
		"GlossDiv": {
            "title": "S",
			"GlossList": {
                "GlossEntry": {
                    "ID": "SGML",
					"SortAs": "SGML",
					"GlossTerm": "Standard Generalized Markup Language",
					"Acronym": "SGML",
					"Abbrev": "ISO 8879:1986",
					"GlossDef": {
                        "para": "A meta-markup language, used to create markup languages such as DocBook.",
						"GlossSeeAlso": ["GML", "XML"]
                    },
					"GlossSee": "markup"
                }
            }
        }
    }
}  )";
  struct input_t *input = input_new(data, strlen(data));

  // Parse our input
  struct ast_t *ast = parse(parser, input);

  // Print our ast
  //display_ast(ast, json_type_strings);

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

  property_type t = conv_ast(ast);
  boost::apply_visitor(printer(std::cout), t);

  ast_recursive_delete(ast);
  input_delete(input);
  parser_delete(parser);

  return 0;
}
