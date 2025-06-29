#include "Serious/ast/lexer.h"
#include "Serious/ast/parser.h"
#include "Serious/ast/token.h"
#include "Serious/debug.h"
#include <iostream>
#include <string>


void execCode(const std::string &code) {
  Serious::Lexer lex(code);
  #ifdef DEBUG
    DEBUG_LOG("Source Code:");
    lex.printCode();
  #endif
  
  try {
    Serious::TokenList tokens = lex.start();
    Serious::Parser parser(tokens);
    parser.parse();
  } catch (const std::exception &e) {
    std::cerr << "----" << std::endl;
    std::cerr << "An error occurred: " << e.what() << std::endl;
  }
}

int main() {
  std::string code;

  while (true) {
    std::cout << ">";
    std::getline(std::cin, code);

    execCode(code);
  }

  return 0;
}