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
        result["text"] = tu->getTextList(context);
        result_stack.top()->push_back(result);
        return nullptr;
    }

};

json runMyVisitor(Java8Parser &parser, antlr4::tree::ParseTree *tree)
{
    MyVisitor v(parser);
    antlrcpp::Any result = v.visit(tree);
    return result.as<json>();
}
