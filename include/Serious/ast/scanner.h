#pragma once

#include "Serious/ast/location.h"
#include <cstddef>
#include <string>

namespace Serious{
  
  class Scanner{
    private:
      std::string code;
      size_t index = 0;
      Position pos;
    public:
      Scanner(std::string source)
        :code(std::move(source)),pos(){}
      
      char nextChar();
      Position getPos() const;
      std::string getCode() const;
      char currentChar();
      char peek() const;
      bool hasNext() const;
  };
  
}