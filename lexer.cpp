//
// Created by irwin on 03/08/2021.
//
#include "lexer.h"

namespace monkey {
    /**
     * helper functions
     */
     bool isLetter(char ch) {
         return isalpha(ch) || ch == '_';
     }

     bool isDigit(char ch) {
         return isdigit(ch);
     }

     /**
      * Private functions
      */
      void Lexer::readChar() {
          if (readPosition >= input.size()) {
              ch = 0;
          } else {
              ch = input[readPosition];
          }
          position = readPosition;
          readPosition += 1;
      }

      char Lexer::peekChar() {
          if (readPosition >= input.size()) {
              return 0;
          }
          return input[readPosition];
      }

      std::string Lexer::readIdentifier() {
          int start = position;
          do {
              readChar();
          } while(ch != 0 && isLetter(ch));

          return input.substr(start, position - start);
      }

      std::string Lexer::readNumber() {
          int start = position;
          do {
              readChar();
          } while(ch != 0 && isDigit(ch));

          return input.substr(start, position - start);
      }

      std::string Lexer::readString() {
          readChar(); // skip first "
          int start = position;
          do {
              readChar();
          } while(ch != 0 && ch != '"');
          int end = position;
          readChar(); // skip last "

          return input.substr(start, end - start);
      }

      void Lexer::skipWhitespace() {
          while(ch != 0 && (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')) {
              readChar();
          }
      }
      /**
       * public functions
       */
       void Lexer::New(std::string& input) {
           this->input = input;
           readPosition = 0;
           readChar();
       }

      Token Lexer::NextToken() {
          Token tok;
          skipWhitespace();
          switch (ch) {
              case '=':
                  if (peekChar() == '=') {
                      tok = Token(EQ, "==");
                      readChar();
                  } else {
                      tok = Token(ASSIGN, '=');
                  }
                  readChar();
                  break;
              case '!':
                  if (peekChar() == '=') {
                      tok = Token(NE, "!=");
                      readChar();
                  } else {
                      tok = Token(BANG, '!');
                  }
                  readChar();
                  break;
              case '<':
                  if (peekChar() == '=') {
                      tok = Token(LE, "<=");
                      readChar();
                  } else {
                      tok = Token(LT, '<');
                  }
                  readChar();
                  break;
              case '>':
                  if (peekChar() == '=') {
                      tok = Token(GE, ">=");
                      readChar();
                  } else {
                      tok = Token(GT, '>');
                  }
                  readChar();
                  break;
              case '+':
                  tok = Token(PLUS, '+');
                  readChar();
                  break;
              case '-':
                  tok = Token(MINUS, '-');
                  readChar();
                  break;
              case '*':
                  tok = Token(ASTERISK, '*');
                  readChar();
                  break;
              case '/':
                  tok = Token(SLASH, '/');
                  readChar();
                  break;
              case '%':
                  tok = Token(PERCENT, '%');
                  readChar();
                  break;
              case '&':
                  tok = Token(REF, '&');
                  readChar();
                  break;
              case '.':
                  tok = Token(DOT, '.');
                  readChar();
                  break;
              case ':':
                  tok = Token(COLON, ':');
                  readChar();
                  break;
              case ',':
                  tok = Token(COMMA, ',');
                  readChar();
                  break;
              case ';':
                  tok = Token(SEMICOLON, ';');
                  readChar();
                  break;
              case '(':
                  tok = Token(LPAREN, '(');
                  readChar();
                  break;
              case ')':
                  tok = Token(RPAREN, ')');
                  readChar();
                  break;
              case '{':
                  tok = Token(LBRACE, '{');
                  readChar();
                  break;
              case '}':
                  tok = Token(RBRACE, '}');
                  readChar();
                  break;
              case '[':
                  tok = Token(LBRACKET, '[');
                  readChar();
                  break;
              case ']':
                  tok = Token(RBRACKET, ']');
                  readChar();
                  break;
              case '"':
                  tok = Token(STRING, readString());
                  break;
              case 0:
                  tok = Token(END, "");
                  readChar();
                  break;
              default:
                  if (isLetter(ch)) {
                      tok.literal = readIdentifier();
                      tok.type = LookupIdent(tok.literal);
                  } else if (isDigit(ch)) {
                      tok.literal = readNumber();
                      tok.type = INT;
                  } else {
                      tok = Token(ILLEGAL, ch);
                      readChar();
                  }
                  break;
          }
          return tok;
      }
}

