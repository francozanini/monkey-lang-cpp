#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"


class Lexer {
private:
  /* data */
  std::string input;
  int position;
  int readPosition;
  char currentChar;

  void readChar();
  void skipWhitespace();
  std::string readIdentifier();
  std::string readInteger();
  char peekChar();
public:
  Lexer(std::string input);
  ~Lexer();
  Token* nextToken();
};

#endif