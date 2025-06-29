#pragma once


#include "Serious/ast/location.h"
#include <string>
#include <vector>

namespace Serious{
  
  using TokenValue = std::string;

  enum class TokenType{
    NUMBER,
    IDENTIFIER,
    ASSIGNMENT,
    STRING,
    OPERATOR,
    KEYWORD,
    SEMICOLON,
    COMMA,
    DOT,
    L_SQUARE,
    R_SQUARE,
    L_PAREN,
    R_PAREN,
    END_OF_FILE
  };
  
  struct Token{
    TokenType type;
    TokenValue value;
    Location location;
    void print() const;
  };
  
  using TokenList = std::vector<Token>;
  std::string getTokenTypeStr(TokenType t);
}