//
// Created by irwin on 05/08/2021.
//
#include "parser.h"

namespace monkey {
    // New
    void Parser::New(Lexer &l) {
        this->l = l;

        // Registramos las funciones PrefixParseFn
        prefixParseFns[IDENT] = &Parser::parseIdentifier;
        prefixParseFns[INT] = &Parser::parseIntegerLiteral;
        prefixParseFns[STRING] = &Parser::parseStringLiteral;
        prefixParseFns[TRUE] = &Parser::parseBooleanLiteral;
        prefixParseFns[FALSE] = &Parser::parseBooleanLiteral;

        // Registramos las funciones InfixParseFn
        infixParseFns[PLUS] = &Parser::parseInfixExpression;

        // Avanzamos un par de Tokens.
        nextToken();
        nextToken();
    }

    // Llenamos el diccionario de precedencias
    std::unordered_map<TokenType, Precedence> precedences ({
        {EQ, EQUALS},
        {NE, EQUALS},
        {LT, COMPARISON},
        {LE, COMPARISON},
        {GT, COMPARISON},
        {GE, COMPARISON},
        {PLUS, TERM},
        {MINUS, TERM},
        {ASTERISK, FACTOR},
        {SLASH, FACTOR},
        {PERCENT, FACTOR},
        {LPAREN, CALL},
        {LBRACKET, INDEX},
    });
    /*********************************************************************************************/
    /* FUNCIONES HELPERS                                                                         */
    /*********************************************************************************************/
    // Avanzamos los tokens
    void Parser::nextToken() {
        curToken = peekToken;
        peekToken = l.NextToken();
    }
    // Devolvemos la precedencia actual
    Precedence Parser::curPrecedence() {
        if (precedences.find(curToken.type) != precedences.end()) {
            return precedences[curToken.type];
        }
        return LOWEST;
    }
    // Verifica si el token actual es el dado.
    bool Parser::curTokenIs(TokenType t) {
        return curToken.type == t;
    }
    // Busca el token dado para ver si tiene función prefix asociada.
    PrefixParseFn Parser::getPrefixFn(TokenType t) {
        if (prefixParseFns.find(t) != prefixParseFns.end()) {
            return prefixParseFns[t];
        }
        return nullptr;
    }
    // Busca el token dado para ver si tiene función infix asociada.
    InfixParseFn Parser::getInfixFn(TokenType t) {
        if (infixParseFns.find(t) != infixParseFns.end()) {
            return infixParseFns[t];
        }
        return nullptr;
    }
    // Reporta un error de función prefix no encontrada para el token dado
    void Parser::noPrefixParseFnError(TokenType t) {
       errors.push_back("No prefix parse function for token: " + t);
    }
    /*********************************************************************************************/
    /* REGLAS DE PRODUCCIÓN                                                                      */
    /*********************************************************************************************/
    // Símbolo de entrada de la producción.
    Program* Parser::parseProgram() {
        auto *program = new Program();

        while (curToken.type != END) {
            auto *stmt = parseStatement();
            if (stmt != nullptr) program->statements.push_back(stmt);
            nextToken();
        }

        return program;
    }
    // parseStatement
    Statement* Parser::parseStatement() {
        if (curToken.type == LET) {
            return parseLetStatement();
        } else if(curToken.type == RETURN) {
            return parseReturnStatement();
        } else {
            return parseExpressionStatement();
        }
    }
    // parseLetStatement
    LetStatement* Parser::parseLetStatement() {
        auto *stmt = new LetStatement(curToken);

        nextToken(); // skip LET
        stmt->name = new Identifier(curToken, curToken.literal);
        nextToken(); // skip identifier
        if (!curTokenIs(ASSIGN)) {
            delete stmt;
            return nullptr;
        }
        nextToken();
        stmt->value = parseExpression(LOWEST);

        return stmt;
    }
    // parseReturnStatement
    ReturnStatement* Parser::parseReturnStatement() {
        auto *stmt = new ReturnStatement(curToken);
        nextToken(); // advance RETURN
        stmt->value = parseExpression(LOWEST);

        return stmt;
    }
    // parseExpressionStatement
    ExpressionStatement* Parser::parseExpressionStatement() {
        auto *stmt = new ExpressionStatement(curToken);
        stmt->expression = parseExpression(LOWEST);
        return stmt;
    }
    // parseExpression
    Expression* Parser::parseExpression(Precedence p) {
        auto prefix = getPrefixFn(curToken.type);
        if (prefix == nullptr) {
            noPrefixParseFnError(curToken.type);
            return nullptr;
        }
        Expression* leftExp = (this->*prefix)(); // Esta es la forma de invocar un método.
        while (p < curPrecedence()) {
            auto infix = getInfixFn(curToken.type);
            if (infix == nullptr) return leftExp;
            leftExp = (this->*infix)(leftExp);
        }
        return leftExp;
    }
    // parseIdentifier
    Expression* Parser::parseIdentifier() {
        auto *exp = new Identifier(curToken, curToken.literal);
        nextToken();
        return exp;
    }
    // parseIntegerLiteral
    Expression* Parser::parseIntegerLiteral() {
        auto *exp = new IntegerLiteral(curToken, std::stoi(curToken.literal));
        nextToken();
        return exp;
    }
    // parseStringLiteral
    Expression* Parser::parseStringLiteral() {
        auto *exp = new StringLiteral(curToken, curToken.literal);
        nextToken();
        return exp;
    }
    // parseBooleanLiteral
    Expression* Parser::parseBooleanLiteral() {
        auto *exp = new BooleanLiteral(curToken, curToken.literal == "true");
        nextToken();
        return exp;
    }
    // parseInfixExpression
    Expression* Parser::parseInfixExpression(Expression* left) {
        auto *exp = new InfixExpression(curToken, left, curToken.literal);
        // obtenemos la precedencia del token infijo (+, -, *, /, ==, !=, <, <=, >, >=)
        // antes de avanzar el token.
        auto precedence = curPrecedence();
        nextToken();

        exp->right = parseExpression(precedence);
        return exp;
    }
}