/**
 * @file DescentParser.hpp
 * @author Bo Thompson (extralife.xyz)
 * @brief module to create a kind of bad parse tree and detect a few syntax errors
 * @version 0.1
 * @date 2024-10-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DESCENTPARSER_HPP
#define DESCENTPARSER_HPP

#include "Scanner/Scanner.hpp"

class CodeNode {
  public:
    CodeNode(const Token& t);
    ~CodeNode();

    Token* getToken();
    CodeNode* getChild();
    CodeNode* getSibling();
    void setChild(CodeNode*);
    void setSibling(CodeNode*);
    void setToken(Token*);
    void setToken(const Token&);

  private:
    CodeNode* child = nullptr;
    CodeNode* sibling = nullptr;
    Token* token = nullptr;
};

class DescentParser {
  public:
    DescentParser();
    DescentParser(const string&);
    void open(const string&);

    CodeNode* parse();

  private:
    Scanner s;
    string getLowercase(const string&);
    bool wordIsForbidden(const string&);

    CodeNode* parse(const list<Token>::iterator&, const list<Token>::iterator&);

    enum class ss {
      START,
      SEEN_IDENTIFIER,
      DECLARED_VARIABLE,
      ARRAY_DECLARATION,
      FUNC_RETURN_TYPE,
      FUNC_NAME,
      FUNC_OPEN,
      FUNC_ARGTYPE,
      FUNC_ARGNAME,
      FUNC_COMMACLOSE,
      PROC_DEF,
      IGNORE,
    };

    enum class fs {
      NONE,
      EXPECTING_FIRST_SEMI,
      EXPECTING_SECOND_SEMI,
    };

    ss state = ss::START;
    fs forState = fs::NONE;
    bool descend = false;
};

#endif