#include "Serious/ast/scanner.h"
#include "Serious/ast/location.h"
#include "Serious/debug.h"
#include <string>
#include <cstddef>


namespace Serious{
  
  Position Scanner::getPos() const{
    return pos;
  }
  
  std::string Scanner::getCode() const{
    return code;
  }
  
  char Scanner::nextChar() {
    if (!hasNext()) {
        DEBUG_LOG("Exception: No more char at index " + std::to_string(index));
        throw std::out_of_range("No more char at index " + std::to_string(index));
    }

    char c = code[index++];
    if (c == '\n') {
        pos.line++;
        pos.col = 1;
    } else {
        pos.col++;
    }
    return c;
  }
  
  char Scanner::peek() const {
    if (index + 1 >= code.size()) {
        DEBUG_LOG("Peek out of range at index " + std::to_string(index + 1));
        throw std::out_of_range("Peek out of range");
    }
    return code[index + 1];
  }
  
  char Scanner::currentChar() {
    if(pos.col == 0) pos.col = 1;
    return code[index];
  }
  
  bool Scanner::hasNext() const{
    return index < code.size();
  }
}
