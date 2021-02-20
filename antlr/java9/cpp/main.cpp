#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "antlr4-util.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "antlr4-runtime.h"
#include "Java8Lexer.h"
//#include "Java8Parser.h"
#include "Java8ParserBaseVisitor.h"

#include "strconv.h"

using namespace antlrcpptest;
using namespace antlr4;

class MyVisitor : public Java8ParserBaseVisitor
{

    // Java8ParserVisitor interface
public:
    virtual antlrcpp::Any visitCompilationUnit(Java8Parser::CompilationUnitContext *context)
    {
        visitChildren(context);
        json j;
        j.push_back(1.23);
        j.push_back("abcはろー");
        return j;
    }
};

int main(int argc, const char *argv[])
{
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8);
    unicode_ostream uout(std::cout, GetConsoleCP());

    std::ifstream ifs("../Test.java");

    ANTLRInputStream input(ifs);
    Java8Lexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    Java8Parser parser(&tokens);
    tree::ParseTree *tree = parser.compilationUnit();

    std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";

    uout << "Parse Tree: " << s << std::endl;
    TreeUtils tu;
    std::string pretty = tu.toPrettyTree(tree, &parser);
    uout << "Pretty: " << pretty << std::endl;
    MyVisitor v;
    //v.visit (parser.compilationUnit());
    antlrcpp::Any result = v.visit(tree);
    uout << GetConsoleCP() << result.as<json>().dump() << std::endl;

    return 0;
}
