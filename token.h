#include <string>

enum class TokenType {
  illegal, 
  eof,
  //literals + identifiers
  identifier,
  integer,

  //operators
  assign,
  plus,
  minus,
  negate,
  divide,
  multiply,
  lt,
  gt,

  //delimiters
  comma,
  semicolon,
  lparen,
  rparen,
  lbrace,
  rbrace,

  //keywords
  function,
  let

};

std::string toString(TokenType type);
TokenType lookupIdentifier(std::string identifier);

class Token {
public:
  const TokenType type;
  const std::string literal;

  Token(TokenType type, std::string literal);
  std::string tokenTypeAsString();
};

