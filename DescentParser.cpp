/**
 * @file DescentParser.cpp
 * @author Bo Thompson (extralife.xyz)
 * @brief implementation of the CodeNode and DecentParser functions
 * @version 0.1
 * @date 2024-10-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "DescentParser.hpp"

/**
 * @brief Construct a new Code Node:: Code Node object
 * 
 * @param t token to copy and save as ours
 */
CodeNode::CodeNode(const Token &t) {
  setToken(new Token(t));
}


/**
 * @brief Destroy the Code Node:: Code Node object
 * 
 */
CodeNode::~CodeNode() {
  if (child)
    delete child;
  if (sibling)
    delete sibling;
  if (token)
    delete token;
}

/**
 * @brief gets the token for this node
 * 
 * @return Token* 
 */
Token* CodeNode::getToken() {
  return token;
}

/**
 * @brief sets the token for this node
 * 
 */
void CodeNode::setToken(Token* t) {
  token = t;
}

/**
 * @brief sets the token for this node, copy version
 * 
 */
void CodeNode::setToken(const Token& t) {
  token = new Token(t);
}

/**
 * @brief gets the child of this node
 * 
 * @return CodeNode* of the child, probably nullptr
 */
CodeNode *CodeNode::getChild() {
  return child;
}

/**
 * @brief get the sibling of this node
 * 
 * @return CodeNode* of the sibling, or maaaaybe a nullptr
 */
CodeNode *CodeNode::getSibling() {
  return sibling;
}

/**
 * @brief set the child of this node
 * 
 * @param c new child pointer
 */
void CodeNode::setChild(CodeNode *c) {
  child = c;
}

/**
 * @brief set the sibling of this node
 * 
 * @param s new sibling pointer
 */
void CodeNode::setSibling(CodeNode *s) {
  sibling = s;
}


/**
 * @brief Construct a new Descent Parser:: Descent Parser object. YOU'D BETTER CALL OPEN NEXT
 * 
 */
DescentParser::DescentParser() {
}

/**
 * @brief Construct a new Descent Parser:: Descent Parser object the safe way
 * 
 * @param fname filename to open for the underlying scanner object
 */
DescentParser::DescentParser(const string &fname) {
  open(fname);
}

/**
 * @brief Open a filename with the underlying scanner object
 * 
 * @param fname 
 */
void DescentParser::open(const string &fname) {
  s.open(fname);

  typemap["int"] = SymbolType::INT;
  typemap["char"] = SymbolType::CHAR;
  typemap["bool"] = SymbolType::BOOL;
}

/**
 * @brief where the magic happens. Creates a parse tree and error tests to be compliant with Assignment 3
 * 
 * @return CodeNode* the root of the parse tree
 */
CodeNode* DescentParser::parse() {
  list<Token> tokenList = s.getTokens();

  if (tokenList.empty())  return nullptr;

  descend = false;
  state = ss::START;
  forState = fs::NONE;

  return parse(tokenList.begin(), tokenList.end());
}

list<Symbol *> DescentParser::getSymbolTable(){
  return SymbolTable;
}

CodeNode* DescentParser::parse(const list<Token>::iterator& t, const list<Token>::iterator& end) {
  if (t == end) return nullptr;

  auto nt = next(t,1);

  CodeNode* thisNode = new CodeNode(*t);

  //figure out next branch
  if ((t->getType() == TokenType::SEMICOLON) ||
      (t->getType() == TokenType::LEFT_BRACE) ||
      (t->getType() == TokenType::RIGHT_BRACE) ||
        ((nt != end) &&
          (
            (nt->getType() == TokenType::LEFT_BRACE) ||
            (nt->getType() == TokenType::RIGHT_BRACE)
          )
        )
  ) { //child
    descend = true;
  }
  else {
    descend = false;
  }

  const string lspell = getLowercase(t->getSpelling());

  if (t->getType() == TokenType::LEFT_BRACE) {
    ++braceDepth;
  }
  else if (t->getType() == TokenType::RIGHT_BRACE) {
    if (braceDepth == 0) {
      cerr << "extra close brace!" << endl;
      exit(-1);
    }
    else {
      --braceDepth;
      if (braceDepth == 0) {
        curScope = 0;
      }
    }
  }

  //check for errors
  switch(state) {
    case ss::START:
      switch (t->getType()) {
        case TokenType::IDENTIFIER:
          if (lspell == "function") {
            curSymbol = new Symbol();
            ++highestScope;
            curSymbol->scope = curScope = highestScope;
            curSymbol->type = SymbolType::FUNCTION;
            state = ss::FUNC_RETURN_TYPE;
          }
          else if (lspell == "procedure") {
            curSymbol = new Symbol();
            ++highestScope;
            curSymbol->scope = curScope = highestScope;
            curSymbol->type = SymbolType::PROCEDURE;
            state = ss::FUNC_NAME;
          }
          else if (lspell == "return") {
            state = ss::IGNORE;
          }
          else if (lspell == "for") {
            forState = fs::EXPECTING_FIRST_SEMI;
          }
          else {
            //this might be a variable declaration
            //if it is, the next token should also be an identifier
            if (nt != end && nt->getType() == TokenType::IDENTIFIER) {
              curSymbol = new Symbol;
              curSymbol->type = typemap[getLowercase(t->getSpelling())];
              curSymbol->scope = curScope;

              state = ss::VARIABLE_NAME;
            }

            else state = ss::SEEN_IDENTIFIER;
          }
        break;
        default:
          //if there's more to this statement, we really don't care
          state = ss::IGNORE;
      }
    break;

    case ss::VARIABLE_NAME: {
      if (checkForbidden(*t)) return nullptr;
      curSymbol->name = t->getSpelling();
      
      state = ss::DECLARED_VARIABLE;
    }
    break;

    case ss::SEEN_IDENTIFIER:
      switch (t->getType()) {
        default:
          state = ss::IGNORE;
      }
    break;

    case ss::DECLARED_VARIABLE:
      switch (t->getType()) {
        case TokenType::LEFT_BRACKET:
          state = ss::ARRAY_DECLARATION;
          curSymbol->isArray = true;
        break;
        case TokenType::COMMA: {
          //save this one
          SymbolTable.push_back(curSymbol);

          //make a note of the last type, cause it's the next one too
          SymbolType temp = curSymbol->type;

          //make the new symbol
          curSymbol = new Symbol;
          curSymbol->type = temp;
          curSymbol->scope = curScope;

          state = ss::VARIABLE_NAME;
        }break;
        default:
          SymbolTable.push_back(curSymbol);
          state = ss::IGNORE;
      }
    break;

    case ss::ARRAY_DECLARATION:
      switch (t->getType()) {
        case TokenType::INTEGER:
          if (stoi(lspell) <= 0) {
            cout << "Syntax error on line " << t->getLine() << ": array declaration size must be a positive integer." << endl;
            exit(-1);
          }
          curSymbol->arraySize = stoi(t->getSpelling());
          SymbolTable.push_back(curSymbol);

          //now show me a close bracket
          if (nt == end || nt->getType() != TokenType::RIGHT_BRACKET ) {
            cerr << "Unexpected token " << nt->getSpelling() << " follows array declaration" << endl;
            exit(-1);
          }

          nt = next(nt);

          //ok is this a comma now?
          if (nt != end && nt->getType() == TokenType::COMMA ) {
            //save this one
            SymbolTable.push_back(curSymbol);

            //make a note of the last type, cause it's the next one too
            SymbolType temp = curSymbol->type;

            //make the new symbol
            curSymbol = new Symbol;
            curSymbol->type = temp;
            curSymbol->scope = curScope;

            state = ss::VARIABLE_NAME;
          }
          else state = ss::IGNORE;
        break;
        default:
          state = ss::IGNORE;
      }
    break;

    case ss::FUNC_RETURN_TYPE:
      setSymbolReturnType(*t);
      state = ss::FUNC_NAME;        
    break;

    case ss::FUNC_NAME:
      switch(t->getType()) {
        case TokenType::IDENTIFIER:
          if (checkForbidden(*t)) return nullptr;
          setSymbolName(*t);
          state = ss::FUNC_OPEN;
        break;
        default:
          state = ss::IGNORE;
      }
    break;

    case ss::FUNC_OPEN:
      curArgs = new list<Symbol*>;
      state = ss::FUNC_ARGTYPE;
    break;

    case ss::FUNC_ARGTYPE:
      if (lspell == "void") {
        SymbolTable.push_back(curSymbol);
        state = ss::IGNORE;
      }
      else {
        curArgs->push_back(new Symbol);
        curArgs->back()->type = typemap[getLowercase(t->getSpelling())];
        curArgs->back()->scope = curScope;
        state = ss::FUNC_ARGNAME;
      }
    break;

    case ss::FUNC_ARGNAME:
      if (checkForbidden(*t)) return nullptr;
      curArgs->back()->name = t->getSpelling();

      //check if this parameter is an array
      if (nt != end && nt->getType() == TokenType::LEFT_BRACKET) {
        curArgs->back()->isArray = true;

        //increment nt to skip some tokens:
        nt = next(nt);  //skip bracket
        curArgs->back()->arraySize = stoi(nt->getSpelling()); //get the array size
        nt = next(nt);  //skip array size
        nt = next(nt);  //skip right bracket
      }
      state = ss::FUNC_COMMACLOSE;
    break;

    case ss::FUNC_COMMACLOSE: {
      switch (t->getType()) {
        case TokenType::COMMA:
          state = ss::FUNC_ARGTYPE;
        break;
        case TokenType::RIGHT_PARENTHESIS:
          curSymbol->arguments = curArgs;

          SymbolTable.push_back(curSymbol);

          state = ss::IGNORE;
        break;
        default: {
          cerr << "Unexpected token " << t->getSpelling() << " has terminated function definition";
          exit(-1);
        }
      }
    }

    case ss::IGNORE:
    default:{}
  }

  //reset for the start of each statement
  if (descend) state = ss::START;
  
  //special handling for for statements
  switch(forState) {
    case fs::EXPECTING_FIRST_SEMI: {
      descend = false;

      if (t->getType() == TokenType::SEMICOLON)
        forState = fs::EXPECTING_SECOND_SEMI;
    };
    break;

    case fs::EXPECTING_SECOND_SEMI:
      descend = false;

      if (t->getType() == TokenType::SEMICOLON)
        forState = fs::NONE;
    break;
    
    default: {};
  }

  if (descend) {
    thisNode->setChild(parse(nt, end));
  }
  else {
    thisNode->setSibling(parse(nt, end));
  }

  return thisNode;
}

void DescentParser::setSymbolReturnType(const Token &t) {
  curSymbol->returnType = typemap[getLowercase(t.getSpelling())];
}

void DescentParser::setSymbolName(const Token &t) {
  curSymbol->name = getLowercase(t.getSpelling());
}

bool DescentParser::checkForbidden(const Token& t) {
  //check for forbidden keyword usage
  const string lspell = getLowercase(t.getSpelling());

  string forbidden[] = {
    "char",
    "function",
    "procedure",
    "void",
    "printf",
    "int",
  };
  #define forbiddenCount 6
  
  for (unsigned int i = 0; i < forbiddenCount; ++i) {
    if (lspell == forbidden[i])  {
      cout << "Syntax error on line " << t.getLine()
        << ": reserved word \"" << t.getSpelling() << "\" cannot be used for the name of a variable."
        << endl;
      error = true;
      return true;
    }
  }

  //check for forbidden scoped-ness
  for (auto s: SymbolTable) {

    if (s->scope == 0) {
      if (s->name == t.getSpelling()) {
        cout << "Error on line " << t.getLine() <<
          ": variable \"" << t.getSpelling() << 
          "\" is already defined globally";  
        error = true;
        return true;
      }
    }
    else if (s->scope == curScope){
      bool collision = false;

      if (s->name == t.getSpelling()) {
        collision = true;
      }

      //check parameter list
      if (s->arguments != nullptr) {
        list<Symbol*> paramList = *(s->arguments);

        for (auto p: paramList) {
          if ((*p).name == t.getSpelling()) {
            collision = true;
            break;
          }
        }
      }

      if (collision) {
        cout << "Error on line " << t.getLine() <<
          ": variable \"" << t.getSpelling() << 
          "\" is already defined locally";  
        error = true;
        return true;
      }
    }
  }

  return false;
}
