// Implementation file for the Dictionary class
// Stores data in a basic Hash Table
// By Dane Iwema

#include "Dictionary.h"
#include "vector"
#include <algorithm>

Dictionary::Dictionary() {
    size = 0;
    count = 0;
    currKeyTwo = 0;
    hashTable = new Entry*[getSize()]{nullptr};
}

Dictionary& Dictionary::operator=(const Dictionary& rhs)
{
    if (this != &rhs)
    {
        clear();
        copy(rhs);
    }
    return *this;
}

void Dictionary::addEntry(Entry* anEntry)
{
    if (count + 1 > (getSize() / 2))
        reHash();
    count++;
    int hashKey = hash(anEntry->getKey(), getSize());
    if (hashTable[hashKey] == nullptr) 
        hashTable[hashKey] = anEntry;
    else {
        int offset = secondHash(anEntry->getKey());
        while(hashTable[hashKey] != nullptr) {
            hashKey = (hashKey + offset) % getSize();
        }
        hashTable[hashKey] = anEntry;
    }
}

Entry* Dictionary::findEntry(string key)
{
    int hashKey = hash(key, getSize());
    if (hashTable[hashKey] == nullptr)
        return nullptr;
    int offset = secondHash(key);
    while (hashTable[hashKey]->getKey() != key) {
        hashKey = (hashKey + offset) % getSize();
        if (hashTable[hashKey] == nullptr)
            return nullptr;  
    }
    return hashTable[hashKey];
}

void Dictionary::printDictionaryInOrder(ostream& outputStream) const
{
    std::vector<Entry*> sortedTable;
    for (int i = 0; i < getSize(); i++) {
        if(hashTable[i] != nullptr)
            sortedTable.push_back(hashTable[i]);
    }
    sort(sortedTable.begin(), sortedTable.end(), [](const Entry* entry1, const Entry* entry2) {
        return entry1->getKey() < entry2->getKey();
    });
    for (const Entry* entry : sortedTable)
        entry->printEntry(outputStream);
    cout << "total entries: " << count << endl;
    cout << "total entries in vector: " << sortedTable.size() << endl;
}



void Dictionary::printDictionaryKeys(ostream& outputStream) const
{
    for (int i = 0; i < getSize(); i++) {
        outputStream << i << " ";
        if(hashTable[i] != nullptr)
            outputStream << hashTable[i]->getKey() << endl;
        else
            outputStream << endl;
    }
}

void Dictionary::clear() {
    for (int i = 0; i < getSize(); i++) {
        if (hashTable[i] != nullptr)
            delete hashTable[i];
    }
    delete[] hashTable;
}

void Dictionary::copy(const Dictionary& orig) {
    count = orig.count;
    size = orig.size;
    currKeyTwo = orig.currKeyTwo;
    hashTable = new Entry*[getSize()]{nullptr};
    for (int i = 0; i < getSize(); i++) {
        if (orig.hashTable[i] != nullptr)
            hashTable[i] = new Entry(*orig.hashTable[i]);
    }
}

unsigned int Dictionary::hash(const string & key, int tableSize) {
    unsigned int hashVal = 0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch;
    return hashVal % tableSize;
}

unsigned int Dictionary::secondHash(const string & key) {
    unsigned int hashVal = 0;
    for (char ch : key)
        hashVal = 37 * hashVal + ch;

    return hashVal % keyTwo[currKeyTwo] + 1;
}

void Dictionary::reHash() {
    size++;
    currKeyTwo++;
    Entry** oldTable = hashTable;
    count = 0;
    hashTable = new Entry*[getSize()]{nullptr};
    for (int i = 0; i < tableSizes[size - 1]; i++) {
        if (oldTable[i] != nullptr) {
            addEntry(oldTable[i]);
        }
    }
    delete[] oldTable;
}

int Dictionary::getSize() const {
    return tableSizes[size];
}