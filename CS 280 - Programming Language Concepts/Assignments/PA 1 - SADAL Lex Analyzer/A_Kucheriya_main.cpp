#include "lex.h"
#include <fstream>
#include <map>
#include <iostream>

int main(int argc, char *argv[]) {
    int lineCounter = 0;
    int identCount = 0;
    int nconstCount = 0;
    int sconstCount = 0;
    int tokensCounter = 0;
    LexItem tok;
    ifstream fin;
    string fileName;
    map<string, Token> identMap;
    map<float, Token> nconstMap;
    map<string, Token> sconstMap;
    bool vFlag = false;
    bool nconstFlag = false;
    bool sconstFlag = false;
    bool identFlag = false;

    if (argc == 1) {
        cerr << "NO SPECIFIED INPUT FILE." << endl;
        return 1;
    }
    else {
        for (int i = 1; i < argc; i++) {
            string argument = argv[i];
            if (argument[0] == '-') {
                if (argument == "-v") {
                    vFlag = true;
                }
                else if (argument == "-all") {
                    vFlag = true;
                    nconstFlag = true;
                    sconstFlag = true;
                    identFlag = true;
                }
                else if (argument == "-nconst") {
                    nconstFlag = true;
                }
                else if (argument == "-sconst") {
                    sconstFlag = true;
                }
                else if (argument == "-ident" || argument == "-id") {
                    identFlag = true;
                }
                else {
                    cerr << "UNRECOGNIZED FLAG {" << argument << "}" << endl;
                    return 1;
                }
            }
            else if (fileName.empty()) {
                fileName = argument;
            } else {
                cerr << "Only one file name is allowed." << endl;
                return 1;
            }
        }
    }

    fin.open(fileName.c_str());
    if (!fin) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        return 1;
    }

    fin.seekg(0, ios::end);
    if(fin.tellg() < 1){
        cerr << "Empty File." << endl;
        return 1;
    }
    else {
        fin.clear();
        fin.seekg(0, ios::beg);
    }

    while ((tok = getNextToken(fin, lineCounter)) != DONE && tok != ERR) {
        tokensCounter++;
        if (tok.GetToken() == IDENT) {
            identMap.insert({tok.GetLexeme(), tok.GetToken()});
        }
        else if (tok.GetToken() == ICONST || tok.GetToken() == FCONST) {
            nconstMap.insert({stof(tok.GetLexeme()), tok.GetToken()});
        }
        else if (tok.GetToken() == SCONST) {
            sconstMap.insert({tok.GetLexeme(), tok.GetToken()});
        }
        
        if (vFlag) {
            operator<<(cout, tok);
        }  
    }
    
    identCount = identMap.size();
    nconstCount = nconstMap.size();
    sconstCount = sconstMap.size();

    if (tok == ERR) {
        operator<<(cout, tok);
        return 1;
    }
    else if (tok == DONE) {
        cout << endl;
        cout << "Lines: " << lineCounter << endl;
        cout << "Total Tokens: " << tokensCounter << endl;
        cout << "Identifiers: " << identCount << endl;
        cout << "Numbers: " << nconstCount << endl;
        cout << "Strings: " << sconstCount << endl;

        if (identFlag) {
            cout << "IDENTIFIERS:" << endl;
            for (auto it = identMap.begin(); it != identMap.end(); it++) {
                cout << it->first << (next(it) != identMap.end() ? ", " : "");
            }
            cout << endl;
        }
        if (nconstFlag) {
            cout << "NUMBERS:" << endl;
            for (auto& num : nconstMap) {
                cout << num.first << endl;
            }
        }
        if (sconstFlag) {
            cout << "STRINGS:" << endl;
            for (auto& str : sconstMap) {
                cout << "'" << str.first << "'" << endl;
            }
        }
    }

    return 0;
}
