#include "Serious/ast/location.h"
#include <string>


namespace Serious{

  std::string Position::toString() const {
    return "Line " + std::to_string(line) + ", Column " + std::to_string(col);
  }
  
  std::string Location::toString() const {
    return "Line " + std::to_string(start.line) + ", Column " + std::to_string(start.col);
  }
}