//
// Created by Andrew on 9/17/2024.
//

#include "SymbolTable.hpp"
#include <iostream>

// Destructor to delete the linked list
SymbolTable::~SymbolTable() {
    deleteList(head);
}

// Function to delete the entire linked list
void SymbolTable::deleteList(SymbolNode* node) { // function takes in a node and deletes the entire linked list
    while (node != nullptr) {
        SymbolNode* temp = node;
        node = node->next;
        delete temp;
    }
}

// Function to insert a new symbol into the linked list
void SymbolTable::insert(const Symbol& symbol) { // function takes in a symbol and inserts it into the linked list
    SymbolNode* newNode = new SymbolNode{symbol, head};
    head = newNode;
}

// Function to lookup a symbol by name
SymbolTable::Symbol* SymbolTable::lookup(const std::string& name) { // function takes in a string and looks up the symbol in the linked list
    SymbolNode* current = head;
    while (current != nullptr) {
        if (current->symbol.name == name) {
            return &current->symbol;
        }
        current = current->next;
    }
    return nullptr;
}

// Function to remove a symbol by name
void SymbolTable::remove(const std::string& name) { // function takes in a string and removes the symbol from the linked list
    SymbolNode* current = head;
    SymbolNode* prev = nullptr;

    while (current != nullptr && current->symbol.name != name) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        return; // Symbol not found
    }

    if (prev == nullptr) {
        head = current->next; // Remove head
    } else {
        prev->next = current->next; // Remove non-head
    }

    delete current;
}
