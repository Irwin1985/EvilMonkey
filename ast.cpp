//
// Created by irwin on 05/08/2021.
//
#include "ast.h"

namespace monkey {
    // Program::TokenLiteral()
    std::string Program::TokenLiteral() {
        if (statements.size()) {
            return statements[0]->String();
        }
        return "";
    }
    // Program::String()
    std::string Program::String() {
        std::string out = "";
        for (auto stmt : statements) {
            out += stmt->String() + '\n';
        }
        return out;
    }

    // BlockStatement::String()
    std::string BlockStatement::String() {
        std::string out = "{";
        for (auto stmt : statements) {
            out += stmt->String() + ";\n";
        }
        return out + '}';
    }

    // ExpressionStatement::String()
    std::string ExpressionStatement::String() {
        if (expression == nullptr) {
            return "";
        }
        return expression->String();
    }

    // PrefixExpression::String()
    std::string PrefixExpression::String() {
        return "(" + op + right->String() + ")";
    }

    // InfixExpression::String()
    std::string InfixExpression::String() {
        return "(" + left->String() + " " + op + " " + right->String() + ")";
    }

    // ArrayLiteral::String()
    std::string ArrayLiteral::String() {
        std::string res = "[";
        int i = 0;
        for (auto elem : elements) {
            i += 1;
            if (i > 1) res += ",";
            res += elem->String();
        }
        return res + "]";
    }

    // IndexExpression::String()
    std::string IndexExpression::String() {
        return array->String() + "[" + index->String() + "]";
    }

    // FunctionLiteral::String()
    std::string FunctionLiteral::String() {
        std::string out = "fn(";
        // Parámetros de la función (si es que tiene)
        if (parameters.size()) {
            int i = 0;
            for (auto param : parameters) {
                i += 1;
                if (i > 1) out += ",";
                out += param->String();
            }
        }
        // Cuerpo de la función
        out += body->String();

        return out;
    }

    // CallExpression::String()
    std::string CallExpression::String() {
        std::string args;
        int i=0;
        for (auto arg : arguments) {
            i += 1;
            if (i > 1) args += ",";
            args += arg->String();
        }
        return function->String() + "(" + args + ")";
    }

    // IfExpression::String()
    std::string IfExpression::String() {
        std::string out = "if (" + condition->String() + ")";
        out += consequence->String();
        if (alternative != nullptr) {
            out += "else" + alternative->String();
        }
        return out;
    }

    // WhileExpression::String()
    std::string WhileExpression::String() {
        std::string out = "while (" + condition->String() + ")";
        out += consequence->String();
        return out;
    }

    // LetStatement::String()
    std::string LetStatement::String() {
        return "let " + name.String() + " = " + value->String();
    }

    // RefStatement::String()
    std::string RefStatement::String() {
        return "ref " + name.String() + " = " + value->String();
    }

    // ReturnStatement::String()
    std::string ReturnStatement::String() {
        return "return " + value->String();
    }
}