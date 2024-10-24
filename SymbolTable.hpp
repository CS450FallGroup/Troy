//
// Created by Andrew on 9/17/2024.
//

#ifndef TROY_SYMBOLTABLE_HPP
#define TROY_SYMBOLTABLE_HPP

#include <string>
#include <vector>

class SymbolTable {
public:
    struct Symbol {
        std::string name;                   // Name of the symbol, used for lookup and removal
        bool isProcedure;                   // Is the symbol a procedure?
        bool isFunction;                    // Is the symbol a function?
        std::vector<std::string> parameters;// Parameters of the function/procedure
        std::string returnType;             // Return type of the function
        std::string dataType;               // Data type of the symbol
        bool isArray;                       // Is the symbol an array?
        int ArraySize;                      // Size of the array
        int scope;                          // Scope of the symbol
        bool isGlobal;                      // Is the symbol global?
        bool isDefined;                     // Has the been symbol defined?
        int location;                       // Location of the symbol

        Symbol(const std::string& name, bool isProcedure, bool isFunction,
               const std::vector<std::string>& parameters,
               const std::string& returnType,
               const std::string& dataType, bool isArray, int arraySize,
               int scope, bool isGlobal, bool isDefined, int location)
                : name(name), isProcedure(isProcedure), isFunction(isFunction),
                  parameters(parameters), returnType(returnType),
                  dataType(dataType),
                  isArray(isArray), ArraySize(arraySize), scope(scope),
                  isGlobal(isGlobal), isDefined(isDefined),
                  location(location) {} // Constructor for the symbol
    };

    struct SymbolNode {
        Symbol symbol;
        SymbolNode* next;
    };

    SymbolTable() : head(nullptr) {}
    ~SymbolTable();

    void insert(const Symbol& symbol);
    Symbol* lookup(const std::string& name);
    void remove(const std::string& name);

private:
    SymbolNode* head;

    void deleteList(SymbolNode* node);
};

#endif //TROY_SYMBOLTABLE_HPP
