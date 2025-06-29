#pragma once


#include <vector>
#include <string>
#include "Serious/ast/token.h"
#include "Serious/ast/node.h"

namespace Serious {

class Parser {
private:
  TokenList tokens;
  size_t current = 0;

  public:
    Parser(const TokenList& tokens_) : tokens(tokens_) {}
    AbstractSyntaxTree parse();
  
  private:
  

    NodePtr parseExpression();
   // NodePtr parseTerm();
   NodePtr parseFactor();
    NodePtr parsePrimary();
    NodePtr parseUnary();
    NodePtr parseStatement();
    NodePtr parseCallExpr(NodePtr callee);
    NodePtr parsePostfix(NodePtr expr);
    
    Token advance();
    Token peek() const;
    Token previous() const;
    Token currentTok() const;
    bool isAtEnd() const;
    
   bool matchToken(Token token, TokenType type, std::string value );
   bool matchTokenType(Token token, TokenType type);
  //  bool check(TokenType type);
    
  };
}