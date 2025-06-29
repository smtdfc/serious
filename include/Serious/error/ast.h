#pragma once

#include "Serious/ast/location.h"
#include <stdexcept>
#include <string>
#include <sstream>

namespace Serious {
  class SyntaxException : public std::runtime_error {
    private:
      std::string message;

    public:
      SyntaxException(const std::string& msg, const Location& loc)
        : std::runtime_error(""), message(formatMessage(msg, loc)) {}

      const char* what() const noexcept override {
        return message.c_str();
      }

    private:
      static std::string formatMessage(const std::string& msg, const Location& loc) {
        std::ostringstream oss;
        oss << "SyntaxError: " << msg << "\n"
            << "  At: Line " << loc.start.line << ", Column " << loc.start.col << "\n";
        return oss.str();
      }
  };
}