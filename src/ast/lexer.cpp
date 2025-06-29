#include "Serious/ast/lexer.h"
#include "Serious/ast/token.h"
#include "Serious/ast/helper.h"
#include "Serious/ast/location.h"
#include "Serious/error/ast.h"
#include "Serious/debug.h"
#include <string>
#include <iostream>


namespace Serious{
  
  void Lexer::printCode() const{
    std::cout<< scanner.getCode() << std::endl;
  }
  
  Token Lexer::getString(char matcher){
      Token token{
          TokenType::STRING,
          ""
      };
      Position startPos = scanner.getPos();
      Position endPos = startPos;
      bool isStringClose = false;
      
      while (scanner.hasNext()) {
        char currentChar = scanner.currentChar();
        if(currentChar == matcher){
            DEBUG_LOG("Found String: "+ token.value + " -> Done!");
            isStringClose = true;
            endPos = scanner.getPos();
            scanner.nextChar();
            break;
        }else token.value += currentChar;
        scanner.nextChar();
      }
     
     token.location = Location(startPos,endPos);

     if(!isStringClose){
         Position currentPos = scanner.getPos();
         DEBUG_LOG("EOF when scanning string: "+ token.value + " -> Done!");
         throw SyntaxException("EOF when scanning !",Location(currentPos,currentPos));
     }
     
      return token;
  }

  Token Lexer::getNumber(){
      Token token{
          TokenType::NUMBER,
          ""
      };
      Position startPos = scanner.getPos();
      Position endPos = startPos;
      bool isDot = false;
      
      while (scanner.hasNext()) {
        char currentChar = scanner.currentChar();
        if(isDigit(currentChar)) token.value+= currentChar;
        else if(currentChar == '.' && !isDot){
            token.value+= ".";
            isDot = true;
            Position currentPos = scanner.getPos();

            if(!scanner.hasNext()){
                 DEBUG_LOG("EOF when scanning number: "+ token.value + " -> Exception!");
                 throw SyntaxException("EOF when scanning !",Location(currentPos,currentPos));
            }
            
            if(!isDigit(scanner.peek())){
                DEBUG_LOG("Found invalid number character: " + std::string(1,scanner.peek()) + " -> Exception !" );
                throw SyntaxException("Unknown character "+ std::string(1,scanner.peek()) +" when scanning !", Location(currentPos,currentPos));
            }
        }else{
            DEBUG_LOG("Found number"+ token.value + " -> Done!");
            break;
        }
        
        scanner.nextChar();
        endPos = scanner.getPos();
      }
     
     token.location = Location(startPos,endPos);
     
     return token;
  }

  Token Lexer::getId(){
      Token token{
          TokenType::IDENTIFIER,
          ""
      };
      Position startPos = scanner.getPos();
      Position endPos = startPos;
      
      while (scanner.hasNext()) {
        char currentChar = scanner.currentChar();
        if(isDigit(currentChar) || isAlpha(currentChar) || currentChar =='_') token.value+= currentChar;
        else {
            DEBUG_LOG("Found identifier "+ token.value + " -> Done!");
            break;
        }
        
        scanner.nextChar();
        endPos = scanner.getPos();
      }
     
     token.location = Location(startPos,endPos);
     
     return token;
  }

  Token Lexer::getOperator() {
        char currentChar = scanner.currentChar();
        Position startPos = scanner.getPos();
        Position endPos = startPos;
        TokenType type;
        std::string op(1, currentChar);
    
        if ((currentChar == '<' || currentChar == '>' || currentChar == '=' || currentChar == '!') && scanner.hasNext()) {
            if (scanner.peek() == '=') {
                op += '=';
                scanner.nextChar();
            }
        }
    
        endPos = scanner.getPos();
    
        if (op == "=") {
            type = TokenType::ASSIGNMENT;
        } else if (op == "+" || op == "-" || op == "*" || op == "/" ||
          op == "==" || op == "!=" || op == "<=" || op == ">=" || op == "<"  || op == ">") {
            type = TokenType::OPERATOR;
        }  else {
            throw SyntaxException("Unknown operator: " + op, Location(startPos, endPos));
        }
        
        scanner.nextChar();
        return Token{
            type,
            op,
            Location(startPos, endPos)
        };
    }
    
  TokenList Lexer::start() {
      TokenList tokens;
      
      while (scanner.hasNext()) {
          char currentChar = scanner.currentChar();
  
          if (isWhitespace(currentChar)) {
              DEBUG_LOG("Found Whitespace -> Skipping!");
              scanner.nextChar();
              continue;
          }else if(isAlpha(currentChar) || currentChar == '_' ){
              DEBUG_LOG("Found Identifier Signal -> Scanning!");
              tokens.push_back(getId());
              continue;
          }else if(currentChar == '"' || currentChar == '\''){
              DEBUG_LOG("Found String Signal -> Scanning!");
              scanner.nextChar();
              tokens.push_back(getString(currentChar));
              continue;
          }else if(isDigit(currentChar)){
              DEBUG_LOG("Found Number Signal -> Scanning!");
              tokens.push_back(getNumber());
              continue;
          }else if(currentChar == '+' ||  currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '!' || currentChar == '=' || currentChar=='<' || currentChar == '>'){
              DEBUG_LOG("Found Operator -> Scanning!");
              tokens.push_back(getOperator());
          }else if(currentChar == '('){
              DEBUG_LOG("Found L Bracket  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::L_PAREN,
                  "(",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == ')'){
              DEBUG_LOG("Found R Bracket  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::R_PAREN,
                  ")",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == '['){
              DEBUG_LOG("Found L Square  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::L_SQUARE,
                  "[",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == ']'){
              DEBUG_LOG("Found ] Square  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::R_SQUARE,
                  "]",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == ','){
              DEBUG_LOG("Found comma  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::COMMA,
                  ",",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == '.'){
              DEBUG_LOG("Found dot  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::DOT,
                  ".",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else if(currentChar == ';'){
              DEBUG_LOG("Found semicolon  -> Done!");
              Position currentPos = scanner.getPos();
              tokens.push_back(Token{
                  TokenType::SEMICOLON,
                  ";",
                  Location(currentPos,currentPos)
              });
              scanner.nextChar();
          }else {
              Position currentPos = scanner.getPos();
              DEBUG_LOG("["+ currentPos.toString()+ "] Found invalid character : " + std::string(1, currentChar) +" -> Exception!");
              throw SyntaxException("Invalid character: " + std::string(1, currentChar),Location(currentPos,currentPos));
          }
      }
      
      Position currentPos = scanner.getPos();
        tokens.push_back(Token{
            TokenType::END_OF_FILE,
            "EOF",
            Location(currentPos,currentPos)
      });

      #ifdef DEBUG
          DEBUG_LOG("List token:");
          for (const Token &tok : tokens) {
              tok.print();
          }
      #endif
  
      return tokens;
  }

}