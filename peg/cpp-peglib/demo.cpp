// (1) Include the header file
#include "peglib.h"
#include <assert.h>
#include <iostream>

using namespace peg;
using namespace std;

int main(void) {
  // (2) Make a parser
#if 0x0
  parser parser(R"(
    # Grammar for Calculator...
    Additive    <- Multitive '+' Additive / Multitive
    Multitive   <- Primary '*' Multitive / Primary
    Primary     <- '(' Additive ')' / Number
    Number      <- < [0-9]+ >
    %whitespace <- [ \t]*
  )");
#else
  parser parser(R"(
    # Grammar for Calculator...
    Additive    <- Multitive '+' Additive / Multitive
    Multitive   <- Primary '*' Multitive / Primary
    Primary     <- '(' Additive ')' / Number
    Number      <- < [0-9]+ >
    %whitespace <- [ \t]*
  )");
#endif

  assert(static_cast<bool>(parser) == true);

  // (3) Setup actions
  parser["Additive"] = [](const SemanticValues &vs) {
    switch (vs.choice()) {
    case 0: // "Multitive '+' Additive"
      return any_cast<double>(vs[0]) + any_cast<double>(vs[1]);
    default: // "Multitive"
      return any_cast<double>(vs[0]);
    }
  };

  parser["Multitive"] = [](const SemanticValues &vs) {
    switch (vs.choice()) {
    case 0: // "Primary '*' Multitive"
      return any_cast<double>(vs[0]) * any_cast<double>(vs[1]);
    default: // "Primary"
      return any_cast<double>(vs[0]);
    }
  };

  parser["Number"] = [](const SemanticValues &vs) {
    return vs.token_to_number<double>();
  };

  // (4) Parse
  parser.enable_packrat_parsing(); // Enable packrat parsing.

  double val;
  parser.parse(" (1 + 2) * 3 ", val);

  std::cout << val << std::endl;

  assert(val == 9);
}
