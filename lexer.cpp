#include <string>
#include "Lexer.h"
#include <iostream>
#include <utility>

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

Token *Lexer::nextToken() {
    Token *token = nullptr;

    this->skipWhitespace();

    switch (this->currentChar) {
        case '=': {
            char nextChar = this->peekChar();
            if (nextChar == '=') {
                this->readChar();
                token = new Token(TokenType::EQ, "==");
            } else {
                token = new Token(TokenType::ASSIGN, "=");
            }
        }
            break;
        case '+':
            token = new Token(TokenType::PLUS, "+");
            break;
        case '(':
            token = new Token(TokenType::LPAREN, "(");
            break;
        case ')':
            token = new Token(TokenType::RPAREN, ")");
            break;
        case '{':
            token = new Token(TokenType::LBRACE, "{");
            break;
        case '}':
            token = new Token(TokenType::RBRACE, "}");
            break;
        case ',':
            token = new Token(TokenType::COMMA, ",");
            break;
        case ';':
            token = new Token(TokenType::SEMICOLON, ";");
            break;
        case '!': {
            char next = this->peekChar();
            if (next == '=') {
                this->readChar();
                token = new Token(TokenType::NOT_EQ, "!=");
            } else {
                token = new Token(TokenType::NEGATE, "!");
            }
        }
            break;
        case '-':
            token = new Token(TokenType::MINUS, "-");
            break;
        case '/':
            token = new Token(TokenType::DIVIDE, "/");
            break;
        case '*':
            token = new Token(TokenType::MULTIPLY, "*");
            break;
        case '<':
            token = new Token(TokenType::LT, "<");
            break;
        case '>':
            token = new Token(TokenType::GT, ">");
            break;
        case '\0':
            token = new Token(TokenType::EOF_, "EOF");
            break;
        default: {
            if (isalpha(this->currentChar)) {
                std::string identifier = this->readIdentifier();
                return new Token(lookupKeyword(identifier), identifier);
            } else if (isdigit(this->currentChar)) {
                return new Token(TokenType::INTEGER, this->readInteger());
            } else {
                std::cout << "illegal token: " << this->currentChar << std::endl;
                return new Token(TokenType::ILLEGAL, "");
            }
        }
    }

    this->readChar();

    return token;
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