//
// Created by irwin on 03/08/2021.
//
#include <iostream>
#include "Repl.h"
#include "Lexer.h"

namespace monkey {
    void Start(std::string mode, std::string& input) {
        if (mode == "repl") {
            // TODO: invocar el repl aquí.
        } else if (mode == "lexer") {
            debugLexer(input);
        } else if (mode == "parser") {
            // TODO: invocar el parser aquí.
        } else if (mode == "interpreter") {
            // TODO: invocar el interprete aquí.
        }
    }

    void debugLexer(std::string& input) {
        Lexer l;
        l.New(input);
        Token tok = l.NextToken();

        while (tok.type != END) {
            std::cout << "<" << tok.type << ", '" << tok.literal << "'" << ">" << std::endl;
            tok = l.NextToken();
        }

        std::cout << "<" << tok.type << ", '" << tok.literal << "'" << ">" << std::endl;
    }
}

