//
// Created by irwin on 03/08/2021.
//

#ifndef EVILMONKEY_REPL_H
#define EVILMONKEY_REPL_H
#include <string>

namespace monkey {
    const std::string VERSION = "1.0";
    void Start(std::string mode, std::string& input);
    void debugLexer(std::string &input);
    void debugParser(std::string &input);
}
#endif //EVILMONKEY_REPL_H
