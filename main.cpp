#include <iostream>
#include <string>
#include "lexer.h"
#include <format>

void assert(bool condition, std::string message) {
  if (!condition) {
    std::cout << "Test failed: " << message << std::endl;
    throw std::runtime_error("Test failed");
  }
}

void test_lexer(Lexer lexer, TokenType expectedTokens[], int expectedTokensLength) {
  for (int i = 0; i < expectedTokensLength; i++) {
    Token* nextToken = lexer.nextToken();
    assert(nextToken->type == expectedTokens[i], std::format("expression {} with type {} is not expected token {}", nextToken->literal, nextToken->tokenTypeAsString(), toString(expectedTokens[i])));
    free(nextToken);
  }
  std::cout << "Test passed" << std::endl;
}

int main()
{
  // basic test
  Lexer lexer = Lexer("=+(){},;");
  TokenType tokens[] = {TokenType::assign, TokenType::plus, TokenType::lparen, TokenType::rparen, TokenType::lbrace, TokenType::rbrace, TokenType::comma, TokenType::semicolon};

  test_lexer(lexer, tokens, 8);

  // test 1

  TokenType expectedTokens[] = {
   TokenType::let, TokenType::identifier,TokenType::assign,  TokenType::integer, TokenType::semicolon,
   TokenType::let, TokenType::identifier, TokenType::assign, TokenType::integer, TokenType::semicolon,
   TokenType::let, TokenType::identifier, TokenType::assign, TokenType::function, TokenType::lparen, TokenType::identifier, TokenType::comma, TokenType::identifier, TokenType::rparen, TokenType::lbrace,
   TokenType::identifier, TokenType::plus, TokenType::identifier, TokenType::semicolon,
   TokenType::rbrace, TokenType::semicolon,
   TokenType::let, TokenType::identifier, TokenType::assign, TokenType::identifier, TokenType::lparen, TokenType::identifier, TokenType::comma, TokenType::identifier, TokenType::rparen, TokenType::semicolon,
   TokenType::negate, TokenType::minus, TokenType::divide, TokenType::multiply, TokenType::integer, TokenType::semicolon,
   TokenType::integer, TokenType::lt, TokenType::integer, TokenType::gt, TokenType::integer, TokenType::semicolon,
   TokenType::eof,
  };
  lexer = Lexer(R"(
    let five = 5;
    let ten = 10;
    let add = fn(x, y) {
      x + y;
    };
    let result = add(five, ten);
    !-/*5;
    5 < 10 > 5;
  )");

  test_lexer(lexer, expectedTokens, 46);

  return 0;
}