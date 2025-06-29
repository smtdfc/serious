#include "Serious/ast/parser.h"
#include "Serious/ast/token.h"
#include "Serious/error/ast.h"
#include "Serious/debug.h"

namespace Serious {
  bool Parser::isAtEnd() const {
    return currentTok().type == TokenType::END_OF_FILE;
  }

  Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
  }
  
  Token Parser::peek() const{
    size_t idx = current + 1;
    return tokens[idx];
  }
  
  Token Parser::previous() const{
    size_t idx = current - 1;
    return tokens[idx];
  }
  
  Token Parser::currentTok() const{
    return tokens[current];
  }
  
  bool Parser::matchToken(Token token, TokenType type, std::string value ){
    return token.type == type && token.value == value;
  }
  
  bool Parser::matchTokenType(Token token, TokenType type){
    return token.type == type;
  }

  NodePtr Parser::parseCallExpr(NodePtr callee) {
    DEBUG_LOG("Parsing call expression ");
    std::vector<NodePtr> args;
  
    if (!matchToken(currentTok(), TokenType::R_PAREN, ")")) {
      DEBUG_LOG("Parsing argument list !");
      do {
        args.push_back(parseExpression());
        if (matchToken(currentTok(), TokenType::COMMA, ",")) {
          advance();
        } else {
          break;
        }
      } while (true);
      
      DEBUG_LOG("Parsed argument list !");
    }
  
    if (!matchToken(currentTok(), TokenType::R_PAREN, ")")) {
      throw SyntaxException("Expected ')' after arguments",currentTok().location);
      //throw std::runtime_error("Expected ')' after arguments");
    }
  
    advance(); // skip ')'
    return std::make_shared<CallExpressionNode>(callee, args);
  }

  NodePtr Parser::parsePrimary() {
    Token tok = currentTok();
    if (tok.type == TokenType::NUMBER) {
      DEBUG_LOG("Parsing Number:");
      tok.print();
      auto node = std::make_shared<NumberNode>(std::stod(tok.value));
      advance();
      return node;
    }
    
    if (tok.type == TokenType:: STRING) {
      advance();
      DEBUG_LOG("Parsing String:");
      tok.print();
      auto node = std::make_shared<StringNode>(tok.value);
      return node;
    }

    if (tok.type == TokenType::IDENTIFIER) {
      advance();
      auto idNode = std::make_shared<IdentifierNode>(tok.value);
      return idNode;
    }

    if (matchToken(tok, TokenType::L_PAREN, "(")) {
      advance();
      NodePtr expr = parseExpression();
      if (!matchToken(currentTok(), TokenType::R_PAREN, ")")) {
        DEBUG_LOG("Expected ')'");
        throw std::runtime_error("Expected ')' !");
      }
      advance();
      return expr;
    }
  
    DEBUG_LOG("Unexpected token in primary()");
    throw std::runtime_error("Unexpected token in primary()");
  }

  NodePtr Parser::parsePostfix(NodePtr expr) {
    while (!isAtEnd()) {
      if (matchTokenType(currentTok(), TokenType::L_PAREN)) {
        advance();
        expr = parseCallExpr(expr);
      }
      else if (matchTokenType(currentTok(), TokenType::DOT)) {
        advance();
        if (!matchTokenType(currentTok(), TokenType::IDENTIFIER)) {
          throw std::runtime_error("Expected identifier after '.'");
        }
        std::string propName = currentTok().value;
        advance();
        NodePtr property = std::make_shared<IdentifierNode>(propName);
        expr = std::make_shared<MemberExpressionNode>(expr, property);
      }
      else {
        break;
      }
    }
    return expr;
  }

  NodePtr Parser::parseUnary() {
    if (isAtEnd()) {
      DEBUG_LOG("Unexpected end of input in primary()");
      throw std::runtime_error("Unexpected end of input while parsing expression");
    }
    
    Token tok = currentTok();
    if (tok.type == TokenType::OPERATOR && (tok.value == "-" || tok.value == "!")) {
      advance();
      char op = tok.value[0];
      auto node = std::make_shared<UnaryOpNode>(op,parseUnary());
      return node;
    }
  
    return parsePostfix(parsePrimary());
  }

  NodePtr Parser::parseFactor() {
    NodePtr node = parseUnary();
    while (!isAtEnd() &&
      (matchToken(currentTok(), TokenType::OPERATOR, "*") ||
       matchToken(currentTok(), TokenType::OPERATOR, "/"))) {
      char op = currentTok().value[0];
      advance();
      NodePtr right = parseUnary();
      auto bin = std::make_shared<BinaryOpNode>(op,node, right);
      node = bin;
    }
    return node;
  }

  NodePtr Parser::parseExpression() {
    NodePtr node = parseFactor();
    while (!isAtEnd() &&
      (matchToken(currentTok(), TokenType::OPERATOR, "+") ||
       matchToken(currentTok(), TokenType::OPERATOR, "-"))) {
      char op = currentTok().value[0];
      advance();
      NodePtr right = parseFactor();
      auto bin = std::make_shared<BinaryOpNode>(op,node,right);
      node = bin;
    }
    return node;
  }

  NodePtr Parser::parseStatement() {
    NodePtr expr = parseExpression();
  
    if (matchTokenType(currentTok(), TokenType::END_OF_FILE)) {
      throw std::runtime_error("Unexpected end of file. Expected ';' to terminate statement.");
    }
    
    advance();
    return std::make_shared<ExpressionStatement>(expr);
  }

  AbstractSyntaxTree Parser::parse(){
    AbstractSyntaxTree ast;
    
    while (!isAtEnd()) {
      NodePtr stmt = parseStatement();
    
      if (stmt) {
        ast.nodes.push_back(stmt);
      }
    
      if (matchToken(currentTok(), TokenType::END_OF_FILE, "EOF")) {
        break;
      }
    }

    #ifdef DEBUG
      DEBUG_LOG("AST");
      printAST(ast);
    #endif
    return ast;
  }

} // namespace Serious