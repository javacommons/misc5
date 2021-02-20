#include "antlr4-runtime.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <string>

namespace jcommons {
namespace antlr4 {

class TreeUtils
{

    ::antlr4::Parser *parser;
    std::string Indents;
    int level;

public:
    TreeUtils(::antlr4::Parser *parser): parser(parser) {}
    TreeUtils(::antlr4::Parser &parser): parser(&parser) {}

    std::vector<std::string> getTextList(::antlr4::tree::ParseTree *t) {
        std::vector<std::string> result;
        if (t->children.size() == 0) {
            result.push_back(t->getText());
            return result;
        }
        for (size_t i = 0; i < t->children.size(); i++) {
            std::vector<std::string> result2 = getTextList(t->children[i]);
            for(auto s: result2)
                result.push_back(s);
        }
        return result;
    }

    std::string toPrettyTree(::antlr4::tree::ParseTree *t)
    {
        level = 0;
        Indents = "  ";
        std::string result = process(t);
        std::regex e1("\\n\\s*\\n");
        result = std::regex_replace(result, e1, "\n");
        return result;
    }

protected:
    std::string process(::antlr4::tree::ParseTree *t)
    {
        if (t->children.size() == 0)
            return ::antlr4::tree::Trees::getNodeText(t, this->parser);
        std::stringstream ss;
        ss << lead(level);
        level++;
        std::string s = ::antlr4::tree::Trees::getNodeText(t, this->parser);
        ss << s << ' ';
        for (size_t i = 0; i < t->children.size(); i++)
        {
            ss << process(t->children[i]);
        }
        level--;
        ss << lead(level);
        return ss.str();
    }

    std::string lead(int level)
    {
        std::stringstream ss;
        if (level > 0)
        {
            ss << '\n';
            for (int cnt = 0; cnt < level; cnt++)
            {
                ss << Indents;
            }
        }
        return ss.str();
    }

};

}
}
