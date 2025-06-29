#pragma once


#include <cstddef>
#include <string>

namespace Serious{
  
  struct Position{
    size_t col = 0;
    size_t line = 0;
    std::string toString() const;

  };
  
  struct Location {
    Position start;
    Position end;
    Location(Position s = {}, Position e = {}) : start(s), end(e) {}
    std::string toString() const;
   };
}