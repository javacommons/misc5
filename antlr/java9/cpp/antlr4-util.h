#include "antlr4-runtime.h"
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <string>

class TreeUtils
{

    std::string Indents;
    int level;

public:
    TreeUtils() {}

    std::string toPrettyTree(antlr4::tree::ParseTree *t, antlr4::Parser *parser)
    {
        level = 0;
        Indents = "  ";
        std::string result = process(t, parser);
        std::regex e1("\\n\\s*\\n");
        result = std::regex_replace(result, e1, "\n");
        return result;
    }

protected:
    std::string process(antlr4::tree::ParseTree *t, antlr4::Parser *parser)
    {
        if (t->children.size() == 0)
            return antlr4::tree::Trees::getNodeText(t, parser);
        std::stringstream ss;
        ss << lead(level);
        level++;
        std::string s = antlr4::tree::Trees::getNodeText(t, parser);
        ss << s << ' ';
        for (int i = 0; i < t->children.size(); i++)
        {
            ss << process(t->children[i], parser);
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
