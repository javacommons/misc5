#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "jcommons.antlr4.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
//#include <stack>
#include <deque>

#include "antlr4-runtime.h"
#include "Java8Lexer.h"
//#include "Java8Parser.h"
#include "Java8ParserBaseListener.h"

#include "strconv.h"

using namespace antlrcpptest;

class MyListener : public Java8ParserBaseListener
{
    antlr4::Parser *parser;
    jcommons::antlr4::TreeUtils *tu;
    std::deque<json> result_stack;
public:
    MyListener(antlr4::Parser *parser): parser(parser)
    {
        this->tu = new jcommons::antlr4::TreeUtils(parser);
        json top = json::array();
        result_stack.push_front(top);
    }
    MyListener(antlr4::Parser &parser): MyListener(&parser) {}
    ~MyListener() { result_stack.pop_front(); }

    // Java8ParserListener interface
public:
    json getJsonResult() {
        json &top = result_stack[0];
        return top;
    }

    virtual void enterImportDeclaration(Java8Parser::ImportDeclarationContext *ctx)
    {
        json self;
        self["rule"] = "importDeclaration";
        self["text"] = tu->getTextList(ctx);
        result_stack.push_front(self);
    }

    virtual void exitImportDeclaration(Java8Parser::ImportDeclarationContext *ctx)
    {
        json &self = result_stack[0];
        json &parent = result_stack[1];
        parent.push_back(self);
        result_stack.pop_front();
    }
};

extern json runMyVisitor(Java8Parser &parser, antlr4::tree::ParseTree *tree);

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
    json visitorResult = runMyVisitor(parser, tree);
    uout << visitorResult.dump(2) << std::endl;

    MyListener listener(parser);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    json l_result = listener.getJsonResult();
    uout << l_result.dump(2) << std::endl;

    return 0;
}
