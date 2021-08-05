//
// Created by irwin on 05/08/2021.
//

#ifndef EVILMONKEY_PARSER_H
#define EVILMONKEY_PARSER_H
#include <string>
#include <unordered_map>
#include <vector>
#include "token.h"
#include "lexer.h"
#include "ast.h"

namespace monkey {
    /**
    * Aquí hay un truco: los tipos PrefixParseFn e InfixParseFn aún no están definidos en la clase Parser.
    * y por eso se crea una supuesta clase Parser justo antes de definir los tipos para que el compilador
    * encuentre las referencias de los diccionarios PrefixParseFn e InfixParseFn. (que jugada más astuta).
    */
    class Parser;

    typedef Expression* (Parser::*PrefixParseFn)(); // prefix
    typedef Expression* (Parser::*InfixParseFn)(Expression* left); // infix

    enum Precedence {
        LOWEST,
        EQUALS,     // ==, !=
        COMPARISON, // <, >, <=, >=
        TERM,       // +, -
        FACTOR,     // *, /
        PREFIX,     // -, !
        CALL,       // foo()
        INDEX,      // bar[1]
    };

    extern std::unordered_map<TokenType, Precedence> precedences;

    class Parser {
    public:
        void New(Lexer& l);

        /**************************************************************/
        // funciones helper
        /**************************************************************/
        std::vector<std::string> Errors() { return errors; }
        Precedence curPrecedence();
        void nextToken();
        bool curTokenIs(TokenType t);
        PrefixParseFn getPrefixFn(TokenType t);
        InfixParseFn getInfixFn(TokenType t);
        void noPrefixParseFnError(TokenType t);

        /**************************************************************/
        // Reglas de producción
        /**************************************************************/
        Program* parseProgram();
        Statement* parseStatement();
        LetStatement* parseLetStatement();
        ReturnStatement* parseReturnStatement();
        ExpressionStatement* parseExpressionStatement();
        Expression* parseExpression(Precedence p);
        Expression* parseIdentifier();
        Expression* parseIntegerLiteral();
        Expression* parseStringLiteral();
        Expression* parseBooleanLiteral();
        Expression* parseInfixExpression(Expression* left);

        /**************************************************************/
        // Lista de propiedades
        /**************************************************************/
        Lexer l;
        Token curToken;
        Token peekToken;
        std::vector<std::string> errors;

        // Las funciones de registro (son diccionarios <TokenType, puntero a función>
        std::unordered_map<TokenType, PrefixParseFn> prefixParseFns;
        std::unordered_map<TokenType, InfixParseFn> infixParseFns;
    };
}
#endif //EVILMONKEY_PARSER_H
