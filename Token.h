//
// Created by irwin on 03/08/2021.
//

#ifndef EVILMONKEY_TOKEN_H
#define EVILMONKEY_TOKEN_H
#include <string>
#include <unordered_map>

namespace monkey {
    typedef std::string TokenType;
    class Token {
    public:
        Token()= default; // Constructor vacío
        Token(TokenType type, std::string literal) : type(type), literal(literal) {}
        Token(TokenType type, char literal) : type(type), literal(std::string(1, literal)){}

        TokenType type;
        std::string literal;
    };

    const TokenType ILLEGAL = "ILLEGAL"; // token ilegal o desconocido.
    const TokenType END = "END"; // usamos END en lugar de EOF porque es reservada en C++.

    const TokenType IDENT = "IDENT"; // para identificadores como foo, bar, x, y, etc
    const TokenType INT = "INT"; // solo soportaremos enteros
    const TokenType STRING = "STRING"; // un string con comillas dobles. "jhon", "doe", etc

    const TokenType ASSIGN = "ASSIGN";
    const TokenType PLUS = "PLUS";
    const TokenType MINUS = "MINUS";
    const TokenType BANG = "BANG";
    const TokenType ASTERISK = "ASTERISK";
    const TokenType SLASH = "SLASH";
    const TokenType PERCENT = "PERCENT"; // modulo o resto.

    const TokenType LT = "LT";
    const TokenType GT = "GT";
    const TokenType LE = "LE";
    const TokenType GE = "GE";

    const TokenType EQ = "EQ";
    const TokenType NE = "NE";

    const TokenType DOT = "DOT";
    const TokenType COLON = "COLON";
    const TokenType COMMA = "COMMA";
    const TokenType SEMICOLON = "SEMICOLON";

    const TokenType LPAREN = "LPAREN";
    const TokenType RPAREN = "RPAREN";
    const TokenType LBRACE = "LBRACE";
    const TokenType RBRACE = "RBRACE";
    const TokenType LBRACKET = "LBRACKET";
    const TokenType RBRACKET = "RBRACKET";

    const TokenType REF = "REF";

    // palabras reservadas
    const TokenType FUNCTION = "FUNCTION";
    const TokenType LET = "LET";
    const TokenType TRUE = "TRUE";
    const TokenType FALSE = "FALSE";
    const TokenType IF = "IF";
    const TokenType ELSE = "ELSE";
    const TokenType RETURN = "RETURN";
    const TokenType WHILE = "WHILE";

    extern std::unordered_map<std::string, TokenType> keywords; // extern para usarla fuera.

    TokenType LookupIdent(std::string ident); // prototipo de la función
}


#endif //EVILMONKEY_TOKEN_H
