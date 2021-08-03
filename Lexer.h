//
// Created by irwin on 03/08/2021.
//

#ifndef EVILMONKEY_LEXER_H
#define EVILMONKEY_LEXER_H
#include "Token.h"
#include <string>

namespace monkey {
    class Lexer {
    public:
        void New(std::string& input);
        Token NextToken();
    private:
        void readChar();
        char peekChar();
        std::string readIdentifier();
        std::string readNumber();
        std::string readString();
        void skipWhitespace();

    std::string input;
    int position;
    int readPosition;
    char ch;
    };
}

#endif //EVILMONKEY_LEXER_H
