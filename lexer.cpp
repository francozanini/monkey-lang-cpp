#include <memory>
#include <string>
#include "Lexer.h"
#include <iostream>
#include <utility>
#include "token.h"
#include <memory>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

Lexer::Lexer(std::string input) {
    this->input = std::move(input);
    this->position = 0;
    this->readPosition = 1;
    this->currentChar = this->input[this->position];
}

Lexer::~Lexer() = default;

char Lexer::peekChar() {
    if (this->readPosition >= this->input.length()) {
        return '\0';
    } else {
        return this->input[this->readPosition];
    }
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

std::unique_ptr<M::Token> Lexer::nextToken() {
    M::Token *token;

    this->skipWhitespace();

    switch (this->currentChar) {
        case '=': {
            char nextChar = this->peekChar();
            if (nextChar == '=') {
                this->readChar();
                token = new M::Token(M::TokenType::EQ, "==");
            } else {
                token = new M::Token(M::TokenType::ASSIGN, "=");
            }
        }
            break;
        case '+':
            token = new M::Token(M::TokenType::PLUS, "+");
            break;
        case '(':
            token = new M::Token(M::TokenType::LPAREN, "(");
            break;
        case ')':
            token = new M::Token(M::TokenType::RPAREN, ")");
            break;
        case '{':
            token = new M::Token(M::TokenType::LBRACE, "{");
            break;
        case '}':
            token = new M::Token(M::TokenType::RBRACE, "}");
            break;
        case ',':
            token = new M::Token(M::TokenType::COMMA, ",");
            break;
        case ';':
            token = new M::Token(M::TokenType::SEMICOLON, ";");
            break;
        case '!': {
            char next = this->peekChar();
            if (next == '=') {
                this->readChar();
                token = new M::Token(M::TokenType::NOT_EQ, "!=");
            } else {
                token = new M::Token(M::TokenType::NEGATE, "!");
            }
        }
            break;
        case '-':
            token = new M::Token(M::TokenType::MINUS, "-");
            break;
        case '/':
            token = new M::Token(M::TokenType::DIVIDE, "/");
            break;
        case '*':
            token = new M::Token(M::TokenType::MULTIPLY, "*");
            break;
        case '<':
            token = new M::Token(M::TokenType::LT, "<");
            break;
        case '>':
            token = new M::Token(M::TokenType::GT, ">");
            break;
        case '\0':
            token = new M::Token(M::TokenType::EOF_, "EOF");
            break;
        default: {
            if (isalpha(this->currentChar)) {
                std::string identifier = this->readIdentifier();
                return std::make_unique<M::Token>(M::lookupKeyword(identifier), identifier);
            } else if (isdigit(this->currentChar)) {
                return std::make_unique<M::Token>(M::TokenType::INTEGER, this->readInteger());
            } else {
                std::cout << "illegal token: " << this->currentChar << std::endl;
                return std::make_unique<M::Token>(M::TokenType::ILLEGAL, "");
            }
        }
    }

    this->readChar();

    return std::unique_ptr<M::Token>(token);
}

void Lexer::skipWhitespace() {
    while (this->currentChar == ' ' || this->currentChar == '\t' || this->currentChar == '\n' ||
           this->currentChar == '\r') {
        this->readChar();
    }
}

std::string Lexer::readIdentifier() {
    std::string literal;
    while (isalpha(this->currentChar)) {
        literal += this->currentChar;
        this->readChar();
    }
    return literal;
}

std::string Lexer::readInteger() {
    std::string literal;
    while (isdigit(this->currentChar)) {
        literal += this->currentChar;
        this->readChar();
    }
    return literal;
}

TEST_CASE("ALL_TOKENS") {
    enum M::TokenType expectedTokens[] = {
            M::TokenType::LET, M::TokenType::IDENTIFIER, M::TokenType::ASSIGN,
            M::TokenType::INTEGER, M::TokenType::SEMICOLON,
            M::TokenType::LET, M::TokenType::IDENTIFIER, M::TokenType::ASSIGN,
            M::TokenType::INTEGER, M::TokenType::SEMICOLON,
            M::TokenType::LET, M::TokenType::IDENTIFIER, M::TokenType::ASSIGN,
            M::TokenType::FUNCTION, M::TokenType::LPAREN,
            M::TokenType::IDENTIFIER, M::TokenType::COMMA, M::TokenType::IDENTIFIER,
            M::TokenType::RPAREN, M::TokenType::LBRACE,
            M::TokenType::IDENTIFIER, M::TokenType::PLUS, M::TokenType::IDENTIFIER,
            M::TokenType::SEMICOLON,
            M::TokenType::RBRACE, M::TokenType::SEMICOLON,
            M::TokenType::LET, M::TokenType::IDENTIFIER, M::TokenType::ASSIGN,
            M::TokenType::IDENTIFIER, M::TokenType::LPAREN,
            M::TokenType::IDENTIFIER, M::TokenType::COMMA, M::TokenType::IDENTIFIER,
            M::TokenType::RPAREN, M::TokenType::SEMICOLON,
            M::TokenType::NEGATE, M::TokenType::MINUS, M::TokenType::DIVIDE, M::TokenType::MULTIPLY,
            M::TokenType::INTEGER,
            M::TokenType::SEMICOLON,
            M::TokenType::INTEGER, M::TokenType::LT, M::TokenType::INTEGER, M::TokenType::GT,
            M::TokenType::INTEGER,
            M::TokenType::SEMICOLON,
            M::TokenType::IF, M::TokenType::LPAREN, M::TokenType::INTEGER, M::TokenType::LT,
            M::TokenType::INTEGER, M::TokenType::RPAREN,
            M::TokenType::LBRACE,
            M::TokenType::RETURN, M::TokenType::TRUE_, M::TokenType::SEMICOLON,
            M::TokenType::RBRACE, M::TokenType::ELSE, M::TokenType::LBRACE,
            M::TokenType::RETURN, M::TokenType::FALSE_, M::TokenType::SEMICOLON,
            M::TokenType::RBRACE,
            M::TokenType::INTEGER, M::TokenType::EQ, M::TokenType::INTEGER, M::TokenType::SEMICOLON,
            M::TokenType::INTEGER, M::TokenType::NOT_EQ, M::TokenType::INTEGER,
            M::TokenType::SEMICOLON,
            M::TokenType::EOF_,
    };

    Lexer lexer = Lexer(R"(
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


    for (auto &expectedToken: expectedTokens) {
        auto nextToken = lexer.nextToken();
        std::string expected = M::toString(expectedToken);
        REQUIRE_EQ(nextToken->tokenTypeAsString(), expected);
    }
}