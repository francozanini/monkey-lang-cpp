#ifndef LEXER_H
#define LEXER_H

#include <string>
#include "token.h"
#include "memory"


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
    explicit Lexer(std::string input);

    ~Lexer();

    std::unique_ptr<M::Token> nextToken();
};

#endif