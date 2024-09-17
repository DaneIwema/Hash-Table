// An dictionary created using a basic binary search tree
// By Mary Elaine Califf

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Entry.h"

class Dictionary
{
private:
    struct Node // struct because I want everything to be public within the Node
    {
        Entry* data;
        Node* left;
        Node* right;
        int height;
        Node(Entry*& theData) : data(theData), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root;

public:
    // Constructor
    Dictionary() : root(nullptr) {}

    // Copy constructor
    Dictionary(const Dictionary& orig) { copy(orig); }

    // Destructor
    ~Dictionary() { clear(); }

    // Assignment operator
    Dictionary& operator=(const Dictionary& rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const { return root == nullptr; }

    // Add an entry
    // Precondition: the dictionary must not already have an Entry with the same key
    // Postcondition: the Entry has been added to the dictionary
    void addEntry(Entry* anEntry);

    // Find an entry
    // Returns nullptr if the entry is not found and the pointer to the Entry if it is
    Entry* findEntry(string key) const;

    // Print entries in order
    // Calls printEntry on each Entry in order
    void printDictionaryInOrder(ostream& outputStream) const;

    // Prints the dictionary keys only, demonstrating the dictionary structure
    // For the binary search tree, this is an easy to do tree format
    void printDictionaryKeys(ostream& outputStream) const;

private:
    // clear helper method for destructor and assignment operator
    void clear() { clear(root); }

    // recursive clear helper method
    void clear(Node* node);

    // copy helper method for destructor and assignment operator
    void copy(const Dictionary& orig) {
        this->root = copy(orig.root);
    }

    // copy helper method for copy constructor and assignment operator
    Node* copy(Node* origNode);

    // recursive helper method for insertion
    void insert(Entry* value, Node*& curPtr);

    // recursive helper for printDictionaryInOrder
    void printInOrder(ostream& outputStream, Node* curNode) const;

    // tree printer helper -- recursive function to print the tree structure
    void printTree(ostream& outputStream, Node* curNode, int depth) const;

    // helper method to get height of the tree
    int height(Node* node) const {return node == nullptr ? -1 : node->height;}

    // balance method
    void balance(Node*& node);

    // single left rotation
    void rotateLeftChild(Node*& node2);

    // double left rotation
    void doubleLeftChild(Node*& node2);

    //single right rotation
    void rotateRightChild(Node*& node2);

    // double right rotation
    void doubleRightChild(Node*& node2);
};

#endif