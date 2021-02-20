#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "jcommons.antlr4.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <stack>

#include "antlr4-runtime.h"
#include "Java8Lexer.h"
//#include "Java8Parser.h"
#include "Java8ParserBaseVisitor.h"

#include "strconv.h"

using namespace antlrcpptest;

class MyVisitor : public Java8ParserBaseVisitor
{
    antlr4::Parser *parser;
    jcommons::antlr4::TreeUtils *tu;
    std::stack<json *> result_stack;

    // Java8ParserVisitor interface
public:
    MyVisitor(antlr4::Parser *parser): parser(parser)
    {
        this->tu = new jcommons::antlr4::TreeUtils(parser);
    }
    MyVisitor(antlr4::Parser &parser): parser(&parser) {}
    virtual antlrcpp::Any visitCompilationUnit(Java8Parser::CompilationUnitContext *context)
    {
        json result = json::array();
        result_stack.push(&result);
        visitChildren(context);
        result_stack.pop();
        return result;
    }

    // Java8ParserVisitor interface
public:
    virtual antlrcpp::Any visitImportDeclaration(Java8Parser::ImportDeclarationContext *context)
    {
        json result;
        result["rule"] = "importDeclaration";
        result_stack.push(&result);
        visitChildren(context);
        result_stack.pop();
        result["text"] = tu->getList(context);
        result_stack.top()->push_back(result);
        return nullptr;
    }

};

int main()
{
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);
    unicode_ostream uout(std::cout, GetConsoleCP());

    std::ifstream ifs("../Test.java");

    antlr4::ANTLRInputStream input(ifs);
    Java8Lexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    Java8Parser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.compilationUnit();

    if(false)
    {
        std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";
        uout << "Parse Tree: " << s << std::endl;
    }

    jcommons::antlr4::TreeUtils tu(parser);
    std::string pretty = tu.toPrettyTree(tree);
    uout << "Pretty: " << pretty << std::endl;
    MyVisitor v(parser);
    antlrcpp::Any result = v.visit(tree);
    uout << GetConsoleCP() << result.as<json>().dump(2) << std::endl;

    return 0;
}
