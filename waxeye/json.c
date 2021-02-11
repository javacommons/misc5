#include <string.h>
#include "json_parser.h"

int main()
{
    // Create our parser
    struct parser_t *parser = json_parser_new();

    // Setup our input
    char data[] = "42";
    struct input_t *input = input_new(data, strlen(data));

    // Parse our input
    struct ast_t *ast = parse(parser, input);

    // Print our ast
    display_ast(ast, json_type_strings);

    printf("type=%d\n", ast->type);

    if(ast->type == AST_TREE)
    {
        printf("AST_TREE\n");
        struct ast_tree_t *tree = ast->data.tree;
        tree->children->size;
    }

    ast_recursive_delete(ast);
    input_delete(input);
    parser_delete(parser);

    return 0;
}
