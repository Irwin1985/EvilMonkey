#include <iostream>
#include "repl.h"
#include "ast.h"

int main() {
    std::string input = "let a = 5 + 10;";

    monkey::Start("parser", input);

    return 0;
}