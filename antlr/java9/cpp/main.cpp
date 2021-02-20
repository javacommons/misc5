#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "antlr4-runtime.h"
#include "Java8Lexer.h"
#include "Java8Parser.h"

#include "strconv.h"

using namespace antlrcpptest;
using namespace antlr4;

class TreeUtils {

    std::string Indents;
    int level;

public:
    TreeUtils() {}

    std::string toPrettyTree(tree::ParseTree *t, antlr4::Parser *parser) {
        level = 0;
        Indents = "  ";
        std::string result = process(t, parser);
        std::regex e1("\\n\\s*\\n");
        result = std::regex_replace(result, e1, "\n");
        return result;
    }

protected:
    std::string process(tree::ParseTree *t, antlr4::Parser *parser) {
        if(t->children.size() == 0) return tree::Trees::getNodeText(t, parser);
        std::stringstream ss;
        ss << lead(level);
        level++;
        std::string s = tree::Trees::getNodeText(t, parser);
        ss << s << ' ';
        for(int i=0; i< t->children.size(); i++) {
          ss << process(t->children[i], parser);
        }
        level--;
        ss << lead(level);
        return ss.str();
    }

    std::string lead(int level) {
        std::stringstream ss;
        if (level > 0) {
            ss << '\n';
            for (int cnt = 0; cnt < level; cnt++) {
                ss << Indents;
            }
        }
        return ss.str();
    }
};

int main(int argc, const char * argv[]) {

  std::ifstream ifs("../Test.java");

  ANTLRInputStream input(ifs);
  Java8Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  Java8Parser parser(&tokens);
  tree::ParseTree *tree = parser.compilationUnit();

  std::wstring s = antlrcpp::s2ws(tree->toStringTree(&parser)) + L"\n";

  //SetConsoleOutputCP(CP_UTF8);
  //SetConsoleCP(CP_UTF8);
  unicode_ostream uout(std::cout, GetConsoleCP());
  uout << "Parse Tree: " << s << std::endl;
  TreeUtils tu;
  std::string pretty = tu.toPrettyTree(tree, &parser);
  uout << "Pretty: " << pretty << std::endl;

  return 0;
}
