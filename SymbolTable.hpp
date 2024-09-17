//
// Created by Andrew on 9/17/2024.
//

#include <string>
#include <vector>

class SymbolTable {
public:
    struct Symbol {
        std::string Name;                                                       // Name of the symbol
        bool isProcedure;                                                       // Is the symbol a procedure?
        bool isFunction;                                                        // Is the symbol a function?
        std::vector<std::string> Parameters;                                    // Parameters of the function
        std::string ReturnType;                                                 // Return type of the function
        bool isGlobal;                                                          // Is the symbol global?
        std::string DataType;                                                   // Data type of the symbol
        bool isArray;                                                           // Is the symbol an array?
        int ArraySize;                                                          // Size of the array
        int DataValue;                                                          // Value of the symbol
        int Scope;                                                              // Scope of the symbol
        bool HasDaughter;                                                       // Does the symbol have a daughter scope?
        int DaughterScope;                                                      // Daughter scope of the symbol
        bool IsDefined;                                                         // Is the symbol defined?
        int Location;                                                           // Location of the symbol
    };

    struct SymbolNode {
        Symbol symbol;                                                          // Symbol
        SymbolNode* next;                                                       // Next node
    };

    SymbolTable() : head(nullptr) {}
    ~SymbolTable();

    void insert(const std::string& name, const Symbol& symbol);                 // Insert a symbol
    Symbol* lookup(const std::string& name);                                    // Lookup a symbol by name
    void remove(const std::string& name);                                       // Remove a symbol by name

private:
    SymbolNode* head;                                                           // Head of the linked list of symbols

    void deleteList(SymbolNode* node);                                          // Delete the linked list of symbols
};

#endif //TROY_SYMBOLTABLE_HPP
