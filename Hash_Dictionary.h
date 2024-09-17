// An dictionary created using a basic Hash Table
// By Dane Iwema

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Entry.h"

class Dictionary
{
private:

    Entry **hashTable;
    int count;
    int size;
    int currKeyTwo = 0;
    int tableSizes[14] = {101, 211, 431, 863, 1733, 3469, 6947, 13901, 27803, 55609, 111227, 222461, 444929, 889871};
    int keyTwo[14] = {97, 199, 421, 859, 1723, 3467, 6917, 13883, 27799, 55603, 111217, 222437, 444901, 889829};

public:
    // Constructor
    Dictionary();

    // Copy constructor
    Dictionary(const Dictionary& orig) { copy(orig); }

    // Destructor
    ~Dictionary() { clear(); }

    // Assignment operator
    Dictionary& operator=(const Dictionary& rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const { return size == 0; }

    // Add an entry
    // Precondition: the dictionary must not already have an Entry with the same key
    // Postcondition: the Entry has been added to the dictionary
    void addEntry(Entry* anEntry);

    // Find an entry
    // Returns nullptr if the entry is not found and the pointer to the Entry if it is
    Entry* findEntry(string key);

    // Print entries in order
    // Calls printEntry on each Entry in order
    void printDictionaryInOrder(ostream& outputStream) const;

    // Prints the dictionary keys only, demonstrating the dictionary structure
    // For the binary search tree, this is an easy to do tree format
    void printDictionaryKeys(ostream& outputStream) const;

private:
    void clear();

    void copy(const Dictionary& orig);

    unsigned int hash(const string & key, int tableSize);

    unsigned int secondHash(const string & key);

    int getSize() const;

    void reHash();
};

#endif