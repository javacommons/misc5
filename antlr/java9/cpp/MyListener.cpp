#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "jcommons.antlr4.h"

#include <iostream>
#include <string>
#include <stack>

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


json runMyListener(Java8Parser &parser, antlr4::tree::ParseTree *tree)
{
    MyListener listener(parser);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    return listener.getJsonResult();
}
