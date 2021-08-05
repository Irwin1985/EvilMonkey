//
// Created by irwin on 03/08/2021.
//
#include <unordered_map>
#include "token.h"

namespace monkey {
    // llenamos el diccionario con la lista de palabras reservadas
    std::unordered_map<std::string, TokenType> keywords({
        {"let", LET},
        {"fn", FUNCTION},
        {"true", TRUE},
        {"false", FALSE},
        {"if", IF},
        {"else", ELSE},
        {"return", RETURN},
        {"while", WHILE}
    });

    // implementación de la función LookupIdent
    monkey::TokenType LookupIdent(std::string ident) {
        if (keywords.find(ident) == keywords.end()) {
            return IDENT;
        }
        return keywords[ident];
    }
}

