#include <string>

enum class TokenType {
  ILLEGAL, 
  EOF_,
  //literals + identifiers
  IDENTIFIER,
  INTEGER,

  //operators
  ASSIGN,
  PLUS,
  MINUS,
  NEGATE,
  DIVIDE,
  MULTIPLY,
  LT,
  GT,
  EQ,
  NOT_EQ,

  //delimiters
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,

  //keywords
  FUNCTION,
  LET,
  IF,
  ELSE,
  RETURN,
  TRUE,
  FALSE

};

std::string toString(TokenType type);
TokenType lookupKeyword(std::string identifier);

class Token {
public:
  const TokenType type;
  const std::string literal;

  Token(TokenType type, std::string literal);
  std::string tokenTypeAsString();
};

