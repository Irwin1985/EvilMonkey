//
// Created by irwin on 05/08/2021.
//

#ifndef EVILMONKEY_AST_H
#define EVILMONKEY_AST_H
#include <string>
#include <vector>
#include "token.h"

namespace monkey {
    /**
     * Interfaces
     * Usaré clases para imitar a las interfaces.
     */
    class Node {
    public:
        virtual ~Node() = default; // Destructor vacío.
        virtual std::string TokenLiteral() = 0; // esto no hace nada en realidad.
        virtual std::string String() = 0; // esto es para imprimir el AST (luego lo haremos con Visitor)
        virtual std::string Type() = 0; // esto si que es importante, devuelve el tipo de nodo.
    };
    /**
    * Clase Statement que deriva de Node.
    * Ejemplo de Statement: let, return, expressionStatement
    */
    class Statement : public Node {
    public:
        virtual void statementNode() = 0;
        virtual std::string TokenLiteral() = 0;
        virtual std::string String() = 0;
        virtual std::string Type() = 0;
    };
    /**
    * Clase Expression que deriva de Node.
    * Ejemplo de Expression: foo, true, 5, "hola", etc.
    */
    class Expression : public Node {
    public:
        virtual void expressionNode() = 0;
        std::string TokenLiteral() = 0;
        std::string String() = 0;
        std::string Type() = 0;
    };
    /**
    * Clase Program que deriva de Statement.
    * Un programa es una colección de sentencias (Statement).
    */
    class Program : public Node {
    public:
        ~Program() override {
            for (auto stmt : statements) {
                delete stmt; // liberamos memoria del array.
            }
        }

        std::string TokenLiteral() override;
        std::string String() override;
        std::string Type() override { return "Program"; } // Retornamos el tipo (sin usar enum)

        std::vector<Statement*> statements; // esta es la declaración de un array.
    };
   /**
    * Clase BlockStatement que deriva de Statement
    * Un BlockStatement es una lista de sentencias (parecido a Program).
    */
    class BlockStatement : public Statement {
    public:
        ~BlockStatement() {
            for (auto stmt : statements) {
                delete stmt; // liberamos la memoria de cada elemento del array.
            }
        }
        void statementNode(){}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() override { return "BlockStatement"; }

        Token token; // '{'
        std::vector<Statement*> statements;
    };
    /**
    * Clase ExpressionStatemt
    */
    class ExpressionStatement : public Statement {
    public:
        ExpressionStatement() = default;
        explicit ExpressionStatement(Token t) { token = t; }
        ~ExpressionStatement() {
            delete expression; // liberamos la expression
        }
        void statementNode(){}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "ExpressionStatement"; }

        Token token;
        Expression* expression;
    };
    /**
    * Clase IntegerLiteral
    */
    class IntegerLiteral : public Expression {
    public:
        IntegerLiteral() = default;
        explicit IntegerLiteral(Token t, int v) { token = t; value = v; }
        void expressionNode() override {}
        std::string TokenLiteral() override { return token.literal; }
        std::string String() override { return std::to_string(value); }
        std::string Type() override { return "IntegerLiteral"; }

        // ~IntegerLiteral() override = 0;
        Token token;
        int value;
    };
    /**
    * Clase StringLiteral
    */
    class StringLiteral : public Expression {
    public:
        StringLiteral() = default;
        explicit StringLiteral(Token t, std::string v) { token = t; value = v; }
        void expressionNode() override {}
        std::string TokenLiteral() override { return token.literal; }
        std::string String() override { return "\"" + value + "\""; };

        std::string Type() override { return "StringLiteral"; }
        Token token;
        std::string value;
    };
    /**
    * BooleanLiteral
    */
    class BooleanLiteral : public Expression {
    public:
        BooleanLiteral() = default;
        explicit BooleanLiteral(Token t, bool v) { token = t; value = v; }
        void expressionNode() override {}
        std::string TokenLiteral() override {return token.literal; }
        std::string String() override { return value ? "true" : "false"; };
        std::string Type() override { return "BooleanLiteral"; }

        Token token;
        bool value;
    };
    /**
    * Identifier
    */
    class Identifier : public Expression {
    public:
        Identifier() = default;
        explicit Identifier(Token t, std::string v) { token = t; value = v;}
        std::string TokenLiteral() override { return token.literal; }
        std::string String() override { return value; };
        std::string Type() override { return "Identifier"; }

        void expressionNode() {}
        Token token;
        std::string value;
    };
    /**
    * PrefixExpression o también conocida como UnaryExpression
    */
    class PrefixExpression : public Expression {
    public:
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "PrefixExpression"; }

        void expressionNode() {}
        Token token;
        std::string op;
        Expression* right; // El nodo de la derecha Ej: -5, !true
    };
    /**
    * InfixExpression o también conocida como BinaryExpression
    */
    class InfixExpression : public Expression {
    public:
        InfixExpression() = default;
        explicit InfixExpression(Token t, Expression* l, std::string o) { token = t; left = l; op = o;}
        std::string TokenLiteral() override { return token.literal; }
        std::string String();
        std::string Type() override { return "InfixExpression"; }

        void expressionNode() {}
        Token token;
        Expression* left;
        std::string op;
        Expression* right;
    };
    /**
    * ArrayLiteral
    */
    class ArrayLiteral : public Expression {
    public:
        ~ArrayLiteral() {
            for (auto elem : elements) {
                delete elem;
            }
        }

        void expressionNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "ArrayLiteral"; }

        Token token;
        std::vector<Expression*> elements;
    };
    /**
    * IndexExpression
    */
    class IndexExpression : public Expression {
    public:
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "IndexExpression"; }

        void expressionNode() {}
        Token token;
        Expression* array;
        Expression* index;
    };
    /**
    * FunctionLiteral
    */
    class FunctionLiteral : public Expression {
    public:
        ~FunctionLiteral() {
            for (auto param : parameters) {
                delete param; // liberamos los items del array.
            }
        }

        void expressionNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "FunctionLiteral"; }

        Token token;
        std::vector<Identifier*> parameters;
        BlockStatement* body;
    };
    /**
    * CallExpression
    */
    class CallExpression : public Expression {
    public:
        // let add = fn(x, y) { return x + y; };
        // add(5, 10); // aquí elimina el puntero de 'add' dejando la función muerta.
        // add(10, 20); // aquí por definición debe ocurrin un NullPointerException porque 'add' no existe.
        ~CallExpression() {
            for (auto arg : arguments) {
                delete arg; // borramos cada uno de los argumentos del array.
            }
            delete function; // ¿por qué aquí si borra el puntero y en las otras no?
        }

        void expressionNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "CallExpression"; }

        Token token;
        Expression* function;
        std::vector<Expression*> arguments;
    };
    /**
    * IfExpression
    */
    class IfExpression : public Expression {
    public:
        void expressionNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "IfExpression"; }

        Token token;
        Expression* condition;
        BlockStatement* consequence;
        BlockStatement* alternative;
    };

    /**
    * WhileExpression
    */
    class WhileExpression : public Expression {
    public:
        void expressionNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "WhileExpression"; }

        Token token;
        Expression* condition;
        BlockStatement* consequence;

    };
    /**
    * LetStatement
    */
    class LetStatement : public Statement {
    public:
        //LetStatement() = default; // constructor vacío
        explicit LetStatement(Token t) { token = t; }
        ~LetStatement() {
            delete value;
        }

        void statementNode() {};
        std::string TokenLiteral() override { return token.literal; }
        std::string String();
        std::string Type() override  { return "LetStatement"; }

        Token token;
        Identifier *name{}; // ¿Por qué una copia y no el puntero?
        Expression* value{};
    };
    /**
    * RefStatement: para sentencias como &a = 6;
    */
    class RefStatement : public Statement {
    public:
        ~RefStatement() {
           // Si value es un puntero a Expression y aquí se borra (que es lo correcto)
           // entonces ¿Por qué los otros AST's que usan punteros no los borran ?
           delete value;
        }

        void statementNode(){}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "RefStatement"; }

        Token token;
        Identifier *name; // ¿ No debería ser un puntero ?
        Expression* value;
    };
    /**
    * ReturnStatement
    */
    class ReturnStatement : public Statement {
    public:
        ReturnStatement() = default;
        explicit ReturnStatement(Token t) { token = t; }
        ~ReturnStatement() {
            delete value;
        }

        void statementNode() {}
        std::string TokenLiteral() { return token.literal; }
        std::string String();
        std::string Type() { return "RefStatement"; }

        Token token;
        Expression* value;
    };
}
#endif //EVILMONKEY_AST_H