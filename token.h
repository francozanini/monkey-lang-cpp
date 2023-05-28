#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace M {
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
        TRUE_,
        FALSE_

    };

    std::string toString(TokenType type);

    TokenType lookupKeyword(const std::string &identifier);

    class Token {
    public:
        const TokenType type;
        const std::string literal;

        Token(TokenType type, std::string literal);

        [[nodiscard]] std::string tokenTypeAsString() const;
    };
}

#endif