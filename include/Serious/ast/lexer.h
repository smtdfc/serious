#pragma once


#include "Serious/ast/token.h"
#include "Serious/ast/scanner.h"
#include <string>

namespace Serious {
  
  class Lexer {
    private:
      Scanner scanner;
    public:
      Lexer(const std::string &source)
        : scanner(source) {}
      void printCode() const;
      TokenList start();
      Token getString(char matcher);
      Token getNumber();
      Token getId();
      Token getOperator();
  };
}