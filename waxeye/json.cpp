#include <string.h>
#include "json_parser.h"

#include "strconv.h"

int main()
{
    using namespace std;

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
