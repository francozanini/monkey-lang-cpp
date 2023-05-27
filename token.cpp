#include "token.h"
#include <iostream>

Token::Token(TokenType type, std::string literal) : type(type), literal(literal) {}

std::string Token::tokenTypeAsString() {
  return toString(this->type);
}

TokenType lookupIdentifier(std::string identifier) {
  if (identifier == "fn") {
    return TokenType::function;
  } else if (identifier == "let") {
    return TokenType::let;
  } else {
    return TokenType::identifier;
  }
}


std::string toString(TokenType type) {
  switch (type) {
    case TokenType::illegal:
      return "ILLEGAL";
    case TokenType::eof:
      return "EOF";
    case TokenType::identifier:
      return "IDENTIFIER";
    case TokenType::integer:
      return "INTEGER";
    case TokenType::assign:
      return "ASSIGN";
    case TokenType::plus:
      return "PLUS";
    case TokenType::comma:
      return "COMMA";
    case TokenType::semicolon:
      return "SEMICOLON";
    case TokenType::lparen:
      return "LPAREN";
    case TokenType::rparen:
      return "RPAREN";
    case TokenType::lbrace:
      return "LBRACE";
    case TokenType::rbrace:
      return "RBRACE";
    case TokenType::function:
      return "FUNCTION";
    case TokenType::let:
      return "LET";
    case TokenType::minus:
      return "MINUS";
    case TokenType::negate:
      return "NEGATE";
    case TokenType::divide:
      return "DIVIDE";
    case TokenType::multiply:
      return "MULTIPLY";
    case TokenType::lt:
      return "LT";
    case TokenType::gt:
      return "GT";
    default: return "UNKNOWN";
    
  }  
};