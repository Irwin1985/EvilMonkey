#include <iostream>
#include "Repl.h"

int main() {
    std::string input = "let fibo = fn(n) { if (n <= 1) { return n; } else {return fibo(n-1) + fibo(n-2); }; };";

    monkey::Start("lexer", input);

    return 0;
}