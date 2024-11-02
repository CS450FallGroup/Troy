/**
 * @file Scanner.cpp
 * @author Bo Thompson (extralife.xyz)
 * @brief there's nothing brief about this. we're reading tokens.
 * @version 0.1
 * @date 2024-09-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "Scanner.hpp"
#include "StringParser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

/**
 * @brief All this does is convert my enums into strings for printing nice and pretty
 * 
 * @param t type to get a good string for
 * @return string that looks good
 */
string getReadableTokenType(TokenType t) {
  //regex to build these:
  //^(\s+)(\w+),*
  //$1case TokenType::$2: return "$2";
  switch (t) {
    case TokenType::NONE: return "NONE";
    case TokenType::IDENTIFIER: return "IDENTIFIER";
    case TokenType::LEFT_PARENTHESIS: return "LEFT_PARENTHESIS";
    case TokenType::RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";
    case TokenType::SEMICOLON: return "SEMICOLON";
    case TokenType::LEFT_BRACE: return "LEFT_BRACE";
    case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
    case TokenType::PLUS: return "PLUS";
    case TokenType::MINUS: return "MINUS";
    case TokenType::DIVIDE: return "DIVIDE";
    case TokenType::ASSIGNMENT: return "ASSIGNMENT";
    case TokenType::INTEGER: return "INTEGER";
    case TokenType::BOOLEAN_EQUAL: return "BOOLEAN_EQUAL";
    case TokenType::SINGLE_QUOTE: return "SINGLE_QUOTE";
    case TokenType::DOUBLE_QUOTE: return "DOUBLE_QUOTE";
    case TokenType::STRING: return "STRING";
    case TokenType::COMMA: return "COMMA";
    case TokenType::MODULO: return "MODULO";
    case TokenType::ASTERISK: return "ASTERISK";
    case TokenType::LESS_THAN: return "LESS_THAN";
    case TokenType::GREATER_THAN: return "GREATER_THAN";
    case TokenType::LESS_THAN_OR_EQUAL: return "LESS_THAN_OR_EQUAL";
    case TokenType::GREATER_THAN_OR_EQUAL: return "GREATER_THAN_OR_EQUAL";
    case TokenType::BOOLEAN_AND: return "BOOLEAN_AND";
    case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
    case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
    case TokenType::BOOLEAN_OR: return "BOOLEAN_OR";
    case TokenType::NOT: return "NOT";
    case TokenType::NOT_EQUAL: return "NOT_EQUAL";
  }

  cerr << "getReadableTokenType: catastrophic failure, unknown token" << endl;
  exit(-1);
  return "";
}

/**
 * @brief Construct a new Scanner. You'd better call open() next.
 * 
 */
Scanner::Scanner() {
}

/**
 * @brief Construct a new Scanner and also call open()
 * 
 * @param fname source file to open
 */
Scanner::Scanner(const string &fname) {
  open(fname);
}

/**
 * @brief Open a source file for tokenization. Leaves the 404 problem up to underlying object SourceReader
 * 
 * @param fname name of the source file
 */
void Scanner::open(const string &fname) {
  sr.open(fname);
}

/**
 * @brief print an error message and end the program, and give a hint about where the failure was
 * 
 * @param msg message to print
 */
void Scanner::error(string msg) {
  cout << "Scanner: " << msg << " at " << sr.getLine() << ":" << sr.getPos() << endl;
  exit(-1);
}

/**
 * @brief The meat of this operation. Returns a linked list full of tokens, can error out in a lot of ways. Hopefully complains about all of them.
 * 
 * @return list<Token> the tokens. empty if a syntax error was found.
 */
list<Token> Scanner::getTokens() {
  list<Token> l;

  //Forgive me, but I have to go all out on macros
  //just this once

  //(\s+)(\w)
  //$1case '$2': \\\n$1
  #define case_af \
    case 'a': \
    case 'b': \
    case 'c': \
    case 'd': \
    case 'e': \
    case 'f':
    
  #define case_AF \
    case 'A': \
    case 'B': \
    case 'C': \
    case 'D': \
    case 'E': \
    case 'F':
    
  #define case_afAF \
    case_af \
    case_AF

  #define case_az \
    case_af \
    case 'g': \
    case 'h': \
    case 'i': \
    case 'j': \
    case 'k': \
    case 'l': \
    case 'm': \
    case 'n': \
    case 'o': \
    case 'p': \
    case 'q': \
    case 'r': \
    case 's': \
    case 't': \
    case 'u': \
    case 'v': \
    case 'w': \
    case 'x': \
    case 'y': \
    case 'z':
    
  #define case_AZ \
    case_AF \
    case 'G': \
    case 'H': \
    case 'I': \
    case 'J': \
    case 'K': \
    case 'L': \
    case 'M': \
    case 'N': \
    case 'O': \
    case 'P': \
    case 'Q': \
    case 'R': \
    case 'S': \
    case 'T': \
    case 'U': \
    case 'V': \
    case 'W': \
    case 'X': \
    case 'Y': \
    case 'Z': 
    
  #define case_azAZ \
    case_az \
    case_AZ

  #define case_azAZ_ \
    case_azAZ \
    case '_':

  #define case_09 \
    case '0': \
    case '1': \
    case '2': \
    case '3': \
    case '4': \
    case '5': \
    case '6': \
    case '7': \
    case '8': \
    case '9': 
  
  #define case_azAZ09_ \
    case_09 \
    case_azAZ_
  
  #define addToList(spelling, type)\
  l.emplace_back(Token ( \
    spelling, \
    type, \
    sr.getLine(), \
    sr.getPos() \
  ))

  //states for the state machine
  enum class ss {
    IDLE,
    INT,
    PLUSMINUS,
    INTEGER,
    EQUAL,
    STRING,
  };

  ss state = ss::IDLE;

  //the spelling of any multi-character variable token we find
  string spelling = "";

  //string parser so that we don't have to think about finding the end of a string
  StringParser sp;

  //iterate through characters in the source file
  char c;
  while (sr.processSource(c)) {
    //switch on state, and inside is a lot of switching on what character we found
    //begin spaghetti code
    switch (state) {
      case ss::IDLE: {
        switch (c) {
          //identifier
          case_azAZ_ {
            spelling += c;

            bool stop = false;

            while (!stop && sr.processSource(c)) {
              switch (c) {
                case_azAZ09_ {
                  spelling += c;
                } break;

                default: {
                  stop = true;
                }
              }
            }
            
            sr.unget(string{c});
            
            addToList(spelling,TokenType::IDENTIFIER);

            spelling = "";

          } break;

          //integers
          case_09 {
            spelling += c;
            state = ss::INTEGER;
          } break;

          //plus or minus, which is probably plus or minus but maybe an integer so go to the disambiguation state
          case '+' :
          case '-' : {
            spelling += c;
            state = ss::PLUSMINUS;
          } break;

          //ampersands are never used in the boolean way it looks like? but he uses the term "boolean_and" instead of "logical_and"
          case '&' : {
            sr.processSource(c);

            if (c != '&') {
              error("Stray &");
            }

            addToList("&&",TokenType::BOOLEAN_AND);

          } break;

          case '|' : {
            sr.processSource(c);

            if (c != '|') {
              error("Stray |");
            }

            addToList("||",TokenType::BOOLEAN_OR);

          } break;

          //< and > cases MIGHT have an equals afterwards, not really worth breaking out into a separate state
          case '<' : {
            sr.processSource(c);

            if (c != '=') {
              sr.unget(string{c});

              addToList("<",TokenType::LESS_THAN);
            }
            else {
              addToList("<=",TokenType::LESS_THAN_OR_EQUAL);
            }
          } break;

          case '>' : {
            sr.processSource(c);
            if (c != '=') {
              sr.unget(string{c});

              addToList(">",TokenType::GREATER_THAN);
            }

            else {

              addToList(">=",TokenType::GREATER_THAN_OR_EQUAL);
            }
          } break;

          case '!' : {
            sr.processSource(c);
            if (c != '=') {
              sr.unget(string{c});

              addToList("!",TokenType::NOT);
            }

            else {

              addToList("!=",TokenType::NOT_EQUAL);
            }
          } break;

          //could be an ==, go to disambiguation state
          case '=' : {
            spelling += c;
            state = ss::EQUAL;
          } break;

          //start of a string. log the type of quote, then feed the quote to our string processor and stop thinking until it says it's our turn again.
          case '\'': {
            addToList(string{c},TokenType::SINGLE_QUOTE);
            state = ss::STRING;
            sp.parse(c);
          } break;

          case '\"': {
            addToList(string{c},TokenType::DOUBLE_QUOTE);
            state = ss::STRING;
            sp.parse(c);
          } break;

          //from here on out there's just a lot of single-character tokens
          case '(' : {
            addToList(string{c},TokenType::LEFT_PARENTHESIS);
          } break;

          case ')' : {
            addToList(string{c},TokenType::RIGHT_PARENTHESIS);
          } break;

          case '%' : {
            addToList(string{c},TokenType::MODULO);
          } break;

          case '*' : {
            addToList(string{c},TokenType::ASTERISK);
          } break;

          case '{' : {
            addToList(string{c},TokenType::LEFT_BRACE);
          } break;

          case '}' : {
            addToList(string{c},TokenType::RIGHT_BRACE);
          } break;

          case ';' : {
            addToList(string{c},TokenType::SEMICOLON);
          } break;

          case ',' : {
            addToList(string{c},TokenType::COMMA);
          } break;

          case '[' : {
            addToList(string{c},TokenType::LEFT_BRACKET);
          } break;

          case ']' : {
            addToList(string{c},TokenType::RIGHT_BRACKET);
          } break;

          case '/' : {
            addToList(string{c},TokenType::DIVIDE);
          } break;

          default: {
            //FIXME: should the idle state report errors on unexpected characters?
          }
        }
      } break;

      //disambiguation between plus/minus and an integer that starts with plus/minus
      case ss::PLUSMINUS: {
        switch (c) {

          case_09 {
            spelling += c;
            state = ss::INTEGER;
          } break;

          default: {
            sr.unget(string{c});
            addToList(spelling,(spelling == "+") ? TokenType::PLUS : TokenType::MINUS);
            spelling = "";
            state = ss::IDLE;
          }
        }
      } break;

      //grab the whole integer
      case ss::INTEGER: {
        switch (c) {
          case_09 {
            spelling += c;

            bool stop = false;

            while (!stop && sr.processSource(c)) {
              switch (c) {
                case_09 {
                  spelling += c;
                } break;

                default: {
                stop = true;
                }
              }
            }

            sr.unget(string{c});
            
            addToList(spelling,TokenType::INTEGER);

            spelling = "";
            state = ss::IDLE;
          } break;

          case_azAZ_ {
            cout << "Syntax error on line " << sr.getLine() << ": invalid integer" << endl;
            l.clear();
            return l;
            
          } break;

          default: {
            sr.unget(string{c});
            
            addToList(spelling,TokenType::INTEGER);

            spelling = "";
            state = ss::IDLE;
          }
        }
      } break;

      //disambiguation between = and ==
      case ss::EQUAL : {
        switch (c) {
          case '=': {
            spelling += "=";

            addToList(spelling,TokenType::BOOLEAN_EQUAL);

            spelling = "";
            state = ss::IDLE;
          } break;

          default: {
            sr.unget(string{c});

            addToList(spelling,TokenType::ASSIGNMENT);

            spelling = "";
            state = ss::IDLE;
          }
        }
      } break;

      //wait for String Parser to say that we've gotten to the end. Until then it's no thoughts, head empty.
      case ss::STRING: {

        while (sp.parse(c)) {
          spelling += c;
          if (!sr.processSource(c)) break;
        }

        addToList(spelling,TokenType::STRING);

        state = ss::IDLE;
        spelling = "";

        if (c == '\'')
          addToList(string{c},TokenType::SINGLE_QUOTE);
        else if (c == '\"')
          addToList(string{c},TokenType::DOUBLE_QUOTE);
        else {
          error("Unexpected character has terminated string");
        }

      } break;

      default: {
        error("Entered unhandled state");
      }
    }
  }

  return l;
}

Token::Token(const Token &other) {
  this->spelling = other.spelling;
  this->type = other.type;
  this->line = other.line;
  this->pos = other.pos;
}