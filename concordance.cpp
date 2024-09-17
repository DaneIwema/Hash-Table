// Program to build a concordance from an input file using a dictionary
// There are two output files, one with the concordance, and one showing the structure of the dictionary
// By Mary Elaine Califf and

#include "Dictionary.h"
#include <fstream>
#include <ctype.h>

// function prototypes

// opens and reads the input file, building the dictionary
void buildDictionary(const string &inFileName, Dictionary &dict);

// open the concordance file and write the dictionary to it
void writeConcordance(const string &outFileName, const Dictionary &dict);

// open the dictionary structure file and write the structure of the dictionary to it
void writeDictionaryStructure(const string &outFileName, const Dictionary &dict);

int main(int argc, char **argv)
{
    // gather the file name arguments
    if (argc < 4)
    {
        // we didn't get enough arguments, so complain and quit
        cout << "Usage: " << argv[0] << " infile concordanceOutputFile dictionaryStructureOutputFile" << endl;
        exit(1);
    }

    string inFileName = argv[1];
    string concFileName = argv[2];
    string dictFileName = argv[3];

    Dictionary dict; // set up the dictionary

    // build the dictionary
    buildDictionary(inFileName, dict);

    // write the dictionary to the concordance file
    writeConcordance(concFileName, dict);

    // write the dictionary structure to the dictionary structure file
    writeDictionaryStructure(dictFileName, dict);
}

void buildDictionary(const string &inFileName, Dictionary &dict)
{
    int lineNumber = 1;
    string curWord = "";

    // open the file
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input" << endl;
        exit(1);
    }

    // YOUR CODE GOES HERE -- feel free to also add additional function(s) if desired

    char character;
    string word;
    while (infile.get(character)) {
        if (isalpha(character))
            word += tolower(character);
        else if (word.length() > 0) {
            Entry *entry = dict.findEntry(word);
            if (entry != nullptr)
                entry->updateEntry(lineNumber);
            else {
                entry = new Entry(word, lineNumber);
                dict.addEntry(entry); 
            }
            word = "";
        }
        if (character == '\n')
            lineNumber++;
    }

    // close the file
    infile.close();
}

void writeConcordance(const string &outFileName, const Dictionary &dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Concordance not written " << endl;
        return;
    }
    dict.printDictionaryInOrder(outfile);
    outfile.close();
}

void writeDictionaryStructure(const string &outFileName, const Dictionary &dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Dictionary structure file not written " << endl;
        return;
    }
    dict.printDictionaryKeys(outfile);
    outfile.close();
}