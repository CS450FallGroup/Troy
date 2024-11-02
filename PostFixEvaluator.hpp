//
// Created by Joshua Lozano on 10/23/24.
//

#ifndef TROY_POSTFIXEVALUATOR_HPP
#define TROY_POSTFIXEVALUATOR_HPP
#include "Scanner.hpp"
#include <map>
#include <stack>
#include <cctype>
#include <vector>
using namespace std;

class PostFixEvaluator {

public:
    PostFixEvaluator();
    bool Eval(Token);
    vector<Token> getEquation();

private:
    map<string, int> Precedence = {
            {"(", -1},{")",-1},{"[",-1},{"]",-1},
            {"!",6},
            {"+", 4},{"-", 4},
            {"*", 5},{"/", 5},{"%", 5},
            {"==",2},{"!=",2},
            {"&&",1},
            {"||",0},
            {"<", 3},{">", 3},{"<=", 3},{">=", 3}};
    vector<Token> PostfixEquation;
    stack<Token> Stack;
    int parenthesis;
    int Brackets;

};


#endif //TROY_POSTFIXEVALUATOR_HPP
