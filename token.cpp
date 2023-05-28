#include "token.h"
#include <iostream>

Token::Token(TokenType type, std::string literal) : type(type), literal(literal) {}

std::string Token::tokenTypeAsString() {
  return toString(this->type);
}

TokenType lookupKeyword(std::string identifier) {
  if (identifier == "fn") {
    return TokenType::FUNCTION;
  } else if (identifier == "let") {
    return TokenType::LET;
  } else if (identifier == "if") {
    return TokenType::IF;
  } else if (identifier == "else") {
    return TokenType::ELSE;
  } else if (identifier == "return") {
    return TokenType::RETURN;
  } else if (identifier == "true") {
    return TokenType::TRUE;
  } else if (identifier == "false") {
    return TokenType::FALSE;
  } else {
    return TokenType::IDENTIFIER;
  }
}


std::string toString(TokenType type) {
  switch (type) {
    case TokenType::ILLEGAL:
      return "ILLEGAL";
    case TokenType::EOF_:
      return "EOF";
    case TokenType::IDENTIFIER:
      return "IDENTIFIER";
    case TokenType::INTEGER:
      return "INTEGER";
    case TokenType::ASSIGN:
      return "ASSIGN";
    case TokenType::PLUS:
      return "PLUS";
    case TokenType::COMMA:
      return "COMMA";
    case TokenType::SEMICOLON:
      return "SEMICOLON";
    case TokenType::LPAREN:
      return "LPAREN";
    case TokenType::RPAREN:
      return "RPAREN";
    case TokenType::LBRACE:
      return "LBRACE";
    case TokenType::RBRACE:
      return "RBRACE";
    case TokenType::FUNCTION:
      return "FUNCTION";
    case TokenType::LET:
      return "LET";
    case TokenType::MINUS:
      return "MINUS";
    case TokenType::NEGATE:
      return "NEGATE";
    case TokenType::DIVIDE:
      return "DIVIDE";
    case TokenType::MULTIPLY:
      return "MULTIPLY";
    case TokenType::LT:
      return "LT";
    case TokenType::GT:
      return "GT";
    case TokenType::EQ:
      return "EQ";
    case TokenType::NOT_EQ:
      return "NOT_EQ";
    case TokenType::IF:
      return "IF";
    case TokenType::ELSE:
      return "ELSE";
    case TokenType::RETURN:
      return "RETURN";
    case TokenType::TRUE:
      return "TRUE";
    case TokenType::FALSE:
      return "FALSE";
    default: {
      std::cout << "Unknown token type: " << static_cast<int>(type) << std::endl;
      return "UNKNOWN";}
    
  }  
};