#include <string>
#include "Lexer.h"
#include <iostream>

Lexer::Lexer(std::string input) {
  this->input = input;
  this->position = 0;
  this->readPosition = 1;
  this->currentChar = this->input[this->position];
}

Lexer::~Lexer() {
}

void Lexer::readChar() {
  if (this->position >= this->input.length()) {
    this->currentChar = '\0';
    return;
  } else {
    this->currentChar = this->input[this->readPosition];
  }

  this->position = this->readPosition;
  this->readPosition++;
}

Token* Lexer::nextToken() {
  Token* token = nullptr; 

  this->skipWhitespace();

  switch (this->currentChar) {
    case '=':
      token = new Token(TokenType::assign, "=");
      break;
    case '+':
      token = new Token(TokenType::plus, "+");
      break;
    case '(':
      token = new Token(TokenType::lparen, "(");
      break;
    case ')':
      token = new Token(TokenType::rparen, ")");
      break;
    case '{':
      token = new Token(TokenType::lbrace, "{");
      break;
    case '}':
      token = new Token(TokenType::rbrace, "}");
      break;
    case ',':
      token = new Token(TokenType::comma, ",");
      break;
    case ';':
      token = new Token(TokenType::semicolon, ";");
      break;
    case '!': 
      token = new Token(TokenType::negate, "!");
      break;
    case '-': 
      token = new Token(TokenType::minus, "-");
      break;
    case '/': 
      token = new Token(TokenType::divide, "/");
      break;
    case '*': 
      token = new Token(TokenType::multiply, "*");
      break;
    case '<': 
      token = new Token(TokenType::lt, "<");
      break;
    case '>': 
      token = new Token(TokenType::gt, ">");
      break;
    default: {
      if (isalpha(this->currentChar)) {
        std::string identifier = this->readIdentifier();
        return new Token(lookupIdentifier(identifier), identifier);
      } else if (isdigit(this->currentChar)) {
        return new Token(TokenType::integer, this->readInteger());
      } else {
        std::cout << "illegal token: " << this->currentChar << std::endl;
        return new Token(TokenType::illegal, "");
      }
    }
  }

  this->readChar();

  return token;
}

void Lexer::skipWhitespace() {
  while (this->currentChar == ' ' || this->currentChar == '\t' || this->currentChar == '\n' || this->currentChar == '\r') {
    this->readChar();
  }
}

std::string Lexer::readIdentifier() {
  std::string literal = "";
  while (isalpha(this->currentChar)) {
    literal += this->currentChar;
    this->readChar();
  }
  return literal;
}

std::string Lexer::readInteger() {
  std::string literal = "";
  while (isdigit(this->currentChar)) {
    literal += this->currentChar;
    this->readChar();
  }
  return literal;
}