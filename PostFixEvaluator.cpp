//
// Created by Joshua Lozano on 10/23/24.
//

#include "PostFixEvaluator.hpp"

PostFixEvaluator::PostFixEvaluator() {
    parenthesis = 0;
}

bool PostFixEvaluator::Eval(Token Symbol) {
    switch (Symbol.getType()){
        case TokenType::INTEGER:
            if(!isdigit(Symbol.getSpelling()[0])){
                Token toke;
                toke.setSpelling(string{Symbol.getSpelling()[0]});
                toke.setType(Symbol.getSpelling()[0] == '+' ?
                             TokenType::PLUS
                             :
                             TokenType::MINUS);
                Eval(toke);
            }
        case TokenType::IDENTIFIER:
            PostfixEquation.push_back(Symbol);
            return true;
        case TokenType::LEFT_BRACKET:
            PostfixEquation.push_back(Symbol);
        case TokenType::LEFT_PARENTHESIS:
            if(Symbol.getType() == TokenType::LEFT_BRACKET){
                Brackets++;
            }
            else{
                parenthesis++;
            }
            Stack.push(Symbol);
            return true;
        case TokenType::RIGHT_BRACKET:
            while(Stack.top().getSpelling() != "["){
                PostfixEquation.push_back(Stack.top());
                Stack.pop();
            }
            PostfixEquation.push_back(Symbol);
            if(Brackets == 0){
                cerr << ("Too many closed Brackets");
                exit(1);
            }
            Brackets--;
            Stack.pop();
            return true;
        case TokenType::RIGHT_PARENTHESIS:
            while(Stack.top().getSpelling() != "("){
                PostfixEquation.push_back(Stack.top());
                Stack.pop();
            }
            if(parenthesis == 0){
                cerr << ("Too many closed Parenthesis");
                exit(1);
            }
            parenthesis--;
            Stack.pop();
            return true;
        case TokenType::NOT:
        case TokenType::ASTERISK:
        case TokenType::DIVIDE:
        case TokenType::MODULO:
        case TokenType::MINUS:
        case TokenType::PLUS:
        case TokenType::GREATER_THAN:
        case TokenType::LESS_THAN:
        case TokenType::GREATER_THAN_OR_EQUAL:
        case TokenType::LESS_THAN_OR_EQUAL:
        case TokenType::BOOLEAN_EQUAL:
        case TokenType::NOT_EQUAL:
        case TokenType::BOOLEAN_AND:
        case TokenType::BOOLEAN_OR:
            if(Stack.empty() || (Precedence[Stack.top().getSpelling()] < Precedence[Symbol.getSpelling()])){
                Stack.push(Symbol);
            }
            else if(Precedence[Stack.top().getSpelling()] == Precedence[Symbol.getSpelling()]){
                PostfixEquation.push_back(Stack.top());
                Stack.pop();
                Stack.push(Symbol);
            }
            else{
                while(!Stack.empty() && (Precedence[Stack.top().getSpelling()] > Precedence[Symbol.getSpelling()])){
                    PostfixEquation.push_back(Stack.top());
                    Stack.pop();
                }
                Stack.push(Symbol);
            }
            return true;
        default:
            while(!Stack.empty()){
                PostfixEquation.push_back(Stack.top());
                Stack.pop();
            }
            return false;
    }
}

vector<Token> PostFixEvaluator::getEquation() {
    return PostfixEquation;
}