#include <iostream>
#include <string>
#include "lexer.h"
#include <format>

void assert(bool condition, const std::string &message) {
    if (!condition) {
        std::cout << "Test failed: " << message << std::endl;
        throw std::runtime_error("Test failed");
    }
}

void test_lexer(Lexer lexer, TokenType expectedTokens[], int expectedTokensLength) {
    for (int i = 0; i < expectedTokensLength; i++) {
        Token *nextToken = lexer.nextToken();
        assert(nextToken->type == expectedTokens[i],
               std::format("expression {} with type {} is not expected token {}",
                           nextToken->literal,
                           nextToken->tokenTypeAsString(),
                           toString(expectedTokens[i])));
        free(nextToken);
    }
    std::cout << "Test passed" << std::endl;
}

int main() {
    // basic test
    Lexer lexer = Lexer("=+(){},;");
    TokenType tokens[] = {TokenType::ASSIGN, TokenType::PLUS, TokenType::LPAREN, TokenType::RPAREN, TokenType::LBRACE,
                          TokenType::RBRACE, TokenType::COMMA, TokenType::SEMICOLON};

    test_lexer(lexer, tokens, 8);

    // test 1

    TokenType expectedTokens[] = {
            TokenType::LET, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INTEGER, TokenType::SEMICOLON,
            TokenType::LET, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::INTEGER, TokenType::SEMICOLON,
            TokenType::LET, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::FUNCTION, TokenType::LPAREN,
            TokenType::IDENTIFIER, TokenType::COMMA, TokenType::IDENTIFIER, TokenType::RPAREN, TokenType::LBRACE,
            TokenType::IDENTIFIER, TokenType::PLUS, TokenType::IDENTIFIER, TokenType::SEMICOLON,
            TokenType::RBRACE, TokenType::SEMICOLON,
            TokenType::LET, TokenType::IDENTIFIER, TokenType::ASSIGN, TokenType::IDENTIFIER, TokenType::LPAREN,
            TokenType::IDENTIFIER, TokenType::COMMA, TokenType::IDENTIFIER, TokenType::RPAREN, TokenType::SEMICOLON,
            TokenType::NEGATE, TokenType::MINUS, TokenType::DIVIDE, TokenType::MULTIPLY, TokenType::INTEGER,
            TokenType::SEMICOLON,
            TokenType::INTEGER, TokenType::LT, TokenType::INTEGER, TokenType::GT, TokenType::INTEGER,
            TokenType::SEMICOLON,
            TokenType::IF, TokenType::LPAREN, TokenType::INTEGER, TokenType::LT, TokenType::INTEGER, TokenType::RPAREN,
            TokenType::LBRACE,
            TokenType::RETURN, TokenType::TRUE, TokenType::SEMICOLON,
            TokenType::RBRACE, TokenType::ELSE, TokenType::LBRACE,
            TokenType::RETURN, TokenType::FALSE, TokenType::SEMICOLON,
            TokenType::RBRACE,
            TokenType::INTEGER, TokenType::EQ, TokenType::INTEGER, TokenType::SEMICOLON,
            TokenType::INTEGER, TokenType::NOT_EQ, TokenType::INTEGER, TokenType::SEMICOLON,
            TokenType::EOF_,
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

    if (5 < 10) {
      return true;
    } else {
      return false;
    }

    10 == 10;
    10 != 9;
  )");

    test_lexer(lexer, expectedTokens, 74);

    return 0;
}