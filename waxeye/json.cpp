#include <string.h>
#include "json_parser.h"

#include "strconv.h"
#include <variant>

void variant01()
{
    // 継承関係にないクラス群
    struct A { void f() {} };
    struct B { void f() {} };
    struct C { void f() {} };

    // A, B, Cのいずれかの型を代入できる型
    std::variant<A, B, C> v = A{}; // A型のオブジェクトを代入
    v = B{}; // B型のオブジェクトに切り替え

    // B型オブジェクトを保持しているか
    if (std::holds_alternative<B>(v)) {
        // 保持しているB型オブジェクトを取得
        B& b = std::get<B>(v);
    }

    // どの型が代入されていたとしても、共通のインタフェースを呼び出す
    std::visit([](auto& x) {
        x.f();
    }, v);

}

int main()
{
    using namespace std;

    variant01();

    // int, char, std::stringのいずれかの型の値を保持できる型
    std::variant<int, char, std::string> v = 3; // int型の値を代入

    // 候補型の0番目の型 (int) を保持しているか
    if (v.index() == 0) {
        int& x = std::get<0>(v); // 型のインデックスを指定して、保持している値を取得
        std::cout << "(1)" << x << std::endl;
    }

    v = std::string("Hello"); // std::string型オブジェクトを代入

    // std::string型を保持しているか
    if (std::holds_alternative<std::string>(v)) {
        std::string& x = std::get<std::string>(v); // 型を指定して、保持している値を取得
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

    if(ast->type == AST_TREE)
    {
        formatA(cout, "AST_TREE\n");
        ast_tree_t *tree = ast->data.tree;
        uout << tree->type << json_type_strings[tree->type] << endl;
        uout << tree->children->size << endl;
        for(size_t i=0; i<tree->children->size; ++i)
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
