#include "Serious/ast/token.h"
#include <iostream>


namespace Serious{
  
  std::string getTokenTypeStr(TokenType t) {
    switch(t) {
      case TokenType::NUMBER:      return "Number";
      case TokenType::IDENTIFIER:  return "Identifier";
      case TokenType::STRING:      return "String";
      case TokenType::ASSIGNMENT:   return "Assignment";
      case TokenType::OPERATOR:    return "Operator";
      case TokenType::KEYWORD:     return "Keyword";
      case TokenType::L_SQUARE:    return "LeftSquare";
      case TokenType::R_SQUARE:    return "RightSquare";
      case TokenType::L_PAREN:     return "LeftParen";
      case TokenType::R_PAREN:     return "RightParen";
      case TokenType::COMMA:    return "Comma";
      case TokenType::DOT:    return "Dot";
      case TokenType::SEMICOLON:    return "Semi";
      case TokenType::END_OF_FILE:         return "EOF";
      default:                     return "Unknown";
    }
  }
  
  
  void Token::print() const{
    std::cout << "Token Type: " << getTokenTypeStr(this->type) << " | Value: " << this->value << std::endl;
  }
  
}