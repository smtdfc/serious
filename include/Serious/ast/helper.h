#include <cctype>
#include <string>


namespace Serious{
  inline bool isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
  }
  
  inline bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
  }
  
  inline bool isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
  }

  inline bool isChar(char c) {
    return std::isprint(c) && c != '\'';
  }

  inline bool isValidEscapeSequence(char c) {
    return c == 'n' || c == 't' || c == '\\' || c == '\'' || c == '"' || c == 'r' || c == '0';
  }

  inline bool isCharacterLiteral(const std::string &str) {
    if (str.length() == 1) {
      return isChar(str[0]);
    } else if (str.length() == 2 && str[0] == '\\') {
      return isValidEscapeSequence(str[1]);
    }
    return false;
  }

}
