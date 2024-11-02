/**
 * @file Scanner.hpp
 * @author Bo Thompson (extralife.xyz)
 * @brief 
 * @version 0.1
 * @date 2024-09-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "SourceReader.h"
#include <string>
#include <list>

using namespace std;

enum class TokenType {
  NONE,
  IDENTIFIER,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  LEFT_BRACE,
  RIGHT_BRACE,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  SEMICOLON,
  PLUS,
  MINUS,
  DIVIDE,
  ASSIGNMENT,
  INTEGER,
  BOOLEAN_EQUAL,
  SINGLE_QUOTE,
  DOUBLE_QUOTE,
  STRING,
  COMMA,
  MODULO,
  ASTERISK,
  LESS_THAN,
  GREATER_THAN,
  LESS_THAN_OR_EQUAL,
  GREATER_THAN_OR_EQUAL,
  BOOLEAN_AND,
  BOOLEAN_OR,
  NOT,
  NOT_EQUAL,
};

string getReadableTokenType(TokenType t);

class Token {
  public:
    Token(){};
    Token(const Token& other);
    Token(string s, TokenType t, unsigned int l, unsigned int p) :
      spelling(s),
      type(t),
      line(l),
      pos(p)
      {};
    string getSpelling() const {return spelling;};
    TokenType getType() {return type;};
    unsigned int getLine() const {return line;};
    unsigned int getPos() {return pos;};

    void setSpelling(string l) {spelling = l;};
    void setType(TokenType t) {type = t;};
    void setLine(unsigned int l) {line = l;};
    void setPos(unsigned int p) {pos = p;};

  private:
    string spelling = "";
    TokenType type = TokenType::NONE;
    unsigned int line = 0;
    unsigned int pos = 0;
};

class Scanner {
  public:
    Scanner();
    Scanner(const string &fname);
    void open(const string &fname);
    list<Token> getTokens();

  private:
    void error(string msg);
    SourceReader sr;
};

#endif