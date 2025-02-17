#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Converts a string to lowercase
string convertToLowercase(string input) 
{
    for (char &ch : input) 
    {
        if (ch >= 'A' && ch <= 'Z') 
        {
            ch += 32;
        }
    }
    return input;
}

// Checks if a given word is a keyword
bool checkIfKeyword(string token) 
{
    string keywords[] = {"begin", "end", "if", "else", "while", "for", "break", "continue", "case", "switch", "class", "public", "private", "abstract", "final"};
    token = convertToLowercase(token);
    
    for (const string &keyword : keywords) 
    {
        if (token == keyword) return true;
    }
    return false;
}

// Checks if a character is an alphabet letter
bool isAlphabet(char ch) 
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

// Checks if a character is a number
bool isNumber(char ch) 
{
    return (ch >= '0' && ch <= '9');
}

// Validates if a given word is a valid identifier
bool validateIdentifier(string token) 
{
    if (token.empty() || !isAlphabet(token[0])) 
    {
        return false;
    }
    
    for (char ch : token) 
    {
        if (!isAlphabet(ch) && !isNumber(ch) && ch != '_') 
        {
            return false;
        }
    }
    return true;
}

// Detects if a word has a special prefix ($, @, %)
char detectSpecialPrefix(string token) 
{
    if (token.empty()) return '\0';
    
    char firstChar = token[0];
    if (firstChar != '$' && firstChar != '@' && firstChar != '%') 
    {
        return '\0';
    }
    
    for (size_t i = 1; i < token.length(); i++) 
    {
        if (!isAlphabet(token[i]) && !isNumber(token[i]) && token[i] != '_') 
        {
            return '\0';
        }
    }
    return firstChar;
}

// Checks if a special token is invalid
bool isInvalidSpecialToken(string token) 
{
    if (token.empty()) return false;
    
    char firstChar = token[0];
    if (firstChar != '$' && firstChar != '@' && firstChar != '%') return false;
    
    for (char ch : token.substr(1)) {
        if (!isAlphabet(ch) && !isNumber(ch) && ch != '_') 
        {
            return true;
        }
    }
    return false;
}

// Checks if a given word is an invalid identifier
bool isInvalidIdentifier(string token) 
{
    if (token.empty() || !isAlphabet(token[0])) return false;
    
    char invalidChars[] = {'.', ',', ':', ')', '\\', '"', ';', '-'};
    for (char ch : token) 
    {
        for (char invalid : invalidChars) 
        {
            if (ch == invalid) return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) 
{
    if (argc < 2) 
    {
        cout << "NO SPECIFIED INPUT FILE NAME.\n";
        return 1;
    }

    string inputFileName = argv[1];
    bool displayKeywords = false, displaySpecials = false, displayIdentifiers = false;

    // Parsing command-line arguments
    for (int i = 2; i < argc; i++) 
    {
        string arg = argv[i];
        if (arg == "-kw") displayKeywords = true;
        if (arg == "-sp") displaySpecials = true;
        if (arg == "-id") displayIdentifiers = true;
    }

    ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) 
    {
        cout << "CANNOT OPEN THE FILE " << inputFileName << "\n";
        return 1;
    }

    int wordCount = 0, keywordCount = 0, identifierCount = 0;
    int dollarSign = 0, atSign = 0, percentSign = 0;
    string token, line;
    int lineNumber = 0;
    bool emptyFile = true;

    // Reading file line by line
    while (getline(inputFile, line)) 
    {
        lineNumber++;
        if (!line.empty()) emptyFile = false;

        token = "";
        for (size_t i = 0; i <= line.length(); i++) 
        {
            if (i == line.length() || line[i] == ' ' || line[i] == '\t') 
            {
                if (!token.empty()) 
                {
                    wordCount++;
                    
                    if (checkIfKeyword(token)) 
                    {
                        keywordCount++;
                    }
                    else 
                    {
                        char specialType = detectSpecialPrefix(token);
                        if (specialType == '$') dollarSign++;
                        else if (specialType == '@') atSign++;
                        else if (specialType == '%') percentSign++;
                        else if (validateIdentifier(token)) 
                        {
                            identifierCount++;
                        }
                        else 
                        {
                            if (isInvalidIdentifier(token) && displayIdentifiers) 
                            {
                                cout << "Invalid Identifier Word at line " << lineNumber << ": " << token << "\n";
                            }
                            else if (isInvalidSpecialToken(token) && displaySpecials) 
                            {
                                cout << "Invalid Special Word at line " << lineNumber << ": " << token << "\n";
                            }
                        }
                    }
                    token = "";
                }
            }
            else 
            {
                token += line[i];
            }
        }
    }

    inputFile.close();

    if (emptyFile) 
    {
        cout << "The File is Empty.\n";
        return 0;
    }

    // Display results
    cout << "Total number of words: " << wordCount << "\n";
    if (displayKeywords) cout << "Number of Keywords: " << keywordCount << "\n";
    if (displayIdentifiers) cout << "Number of Identifiers: " << identifierCount << "\n";
    if (displaySpecials) 
    {
        cout << "Number of Special Words Starting with $: " << dollarSign << "\n";
        cout << "Number of Special Words Starting with @: " << atSign << "\n";
        cout << "Number of Special Words Starting with %: " << percentSign << "\n";
    }

    return 0;
}