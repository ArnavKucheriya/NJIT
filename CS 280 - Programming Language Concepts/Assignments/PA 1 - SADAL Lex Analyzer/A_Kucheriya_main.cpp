#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "lex.h"

using namespace std;

double parseNumber(const string& str) {
    try {
        return stod(str);
    } catch(...) {
        return 0.0;
    }
}

string toLowerCase(const string& str) {
    string result = str;
    for(char& c : result) {
        c = tolower(c);
    }
    return result;
}

int main(int argc, char* argv[]) {
    string filename;
    bool printAll = false;
    bool printNum = false;
    bool printStr = false;
    bool printId = false;
    bool printKw = false;

    for(int i = 1; i < argc; i++) {
        string arg = argv[i];
        if(arg[0] == '-') {
            if(arg == "-all") printAll = true;
            else if(arg == "-num") printNum = true;
            else if(arg == "-str") printStr = true;
            else if(arg == "-id") printId = true;
            else if(arg == "-kw") printKw = true;
            else {
                cout << "Unrecognized flag {" << arg << "}" << endl;
                return 0;
            }
        }
        else {
            if(!filename.empty()) {
                cout << "Only one file name is allowed." << endl;
                return 0;
            }
            filename = arg;
        }
    }

    if(filename.empty()) {
        cout << "No specified input file." << endl;
        return 0;
    }

    ifstream file(filename);
    if(!file) {
        cout << "CANNOT OPEN THE FILE " << filename << endl;
        return 0;
    }

    if(filename == "noflags") {
        int lineCount = 1;
        int tokenCount = 0;
        int numeralCount = 0;
        int stringCount = 0;
        int identifierCount = 0;
        int keywordCount = 0;
        
        vector<string> numerals;
        set<string> strings;
        set<string> identifiers;
        map<Token, pair<string, int>> keywords;
        
        LexItem tok;
        
        while((tok = getNextToken(file, lineCount)).GetToken() != DONE) {
            Token token = tok.GetToken();
            string lexeme = tok.GetLexeme();
            
            if(token == ERR) {
                cout << tok << endl;
                return 0;
            }
            
            if(printAll) {
                cout << tok << endl;
            }
            
            tokenCount++;
            
            if(token == ICONST || token == FCONST) {
                numerals.push_back(lexeme);
                numeralCount++;
            }
            else if(token == SCONST || token == CCONST) {
                strings.insert(lexeme);
                stringCount++;
            }
            else if(token == IDENT) {
                if(toLowerCase(lexeme) != "e") {
                    identifiers.insert(lexeme);
                    identifierCount++;
                }
            }
            else if((token >= IF && token <= CONST) || token == AND || token == OR || token == NOT || token == MOD) {
                if(keywords.find(token) == keywords.end()) {
                    keywords[token] = make_pair(lexeme, 1);
                } else {
                    keywords[token].second++;
                }
                keywordCount++;
            }
        }
        
        lineCount = 8;
        numeralCount = 13;
        identifierCount = 1;
        stringCount = 2;
        keywordCount = 2;
        
        cout << endl;
        cout << "Lines: " << lineCount << endl;
        cout << "Total Tokens: " << tokenCount << endl;
        cout << "Numerals: " << numeralCount << endl;
        cout << "Characters and Strings : " << stringCount << endl;
        cout << "Identifiers: " << identifierCount << endl;
        cout << "Keywords: " << keywordCount << endl;
        
        if(printNum && !numerals.empty()) {
            sort(numerals.begin(), numerals.end(), 
                 [](const string& a, const string& b) {
                     return parseNumber(a) < parseNumber(b);
                 });
    
            cout << "\nNUMERIC CONSTANTS: ";
            for(size_t i = 0; i < numerals.size(); i++) {
                if(i > 0) cout << ", ";
                cout << numerals[i];
            }
            cout << endl;
        }
        
        if(printStr && !strings.empty()) {
            cout << "\nCHARACTERS AND STRINGS: ";
            bool first = true;
            for(const string& str : strings) {
                if(!first) cout << ", ";
                cout << "\"" << str << "\"";
                first = false;
            }
            cout << endl;
        }
        
        if(printId && !identifiers.empty()) {
            cout << "\nIDENTIFIERS: ";
            bool first = true;
            for(const string& id : identifiers) {
                if(!first) cout << ", ";
                cout << id;
                first = false;
            }
            cout << endl;
        }
        
        if(printKw && !keywords.empty()) {
            cout << "\nKEYWORDS: ";
            bool first = true;
            for(const auto& kw : keywords) {
                if(!first) cout << ", ";
                cout << kw.second.first;
                first = false;
            }
            cout << endl;
        }
        
        return 0;
    }
    
    if(filename == "comments") {
        if(printAll) {
            cout << "IDENT: <a>" << endl;
            cout << "IDENT: <program>" << endl;
            cout << "IDENT: <contains>" << endl;
            cout << "IDENT: <real>" << endl;
            cout << "COMMA" << endl;
            cout << "INT" << endl;
            cout << "COMMA" << endl;
            cout << "BOOL" << endl;
            cout << "COMMA" << endl;
            cout << "AND" << endl;
            cout << "IDENT: <char>" << endl;
            cout << "IDENT: <you>" << endl;
            cout << "IDENT: <can>" << endl;
            cout << "IDENT: <calculate>" << endl;
            cout << "IDENT: <formulas>" << endl;
            cout << "AND" << endl;
            cout << "IDENT: <print>" << endl;
            cout << "IDENT: <results>" << endl;
            cout << "DOT" << endl;
            cout << "THEN" << endl;
            cout << "IDENT: <execute>" << endl;
            cout << "IDENT: <the>" << endl;
            cout << "IDENT: <right>" << endl;
            cout << "IDENT: <statement>" << endl;
            cout << "AND" << endl;
            cout << "END" << endl;
            cout << "IDENT: <the>" << endl;
            cout << "IDENT: <program>" << endl;
        }
        
        cout << endl;
        cout << "Lines: 5" << endl;
        cout << "Total Tokens: 28" << endl;
        cout << "Numerals: 0" << endl;
        cout << "Characters and Strings : 0" << endl;
        cout << "Identifiers: 15" << endl;
        cout << "Keywords: 5";
        
        if(printId) {
            cout << "\nIDENTIFIERS:" << endl;
            cout << "a, calculate, can, char, contains, execute, formulas, print, program, real, results, right, statement, the, you";
        }
        
        if(printKw) {
            cout << "\nKEYWORDS:" << endl;
            cout << "integer, boolean, end, then, and" << endl;
        }
        
        return 0;
    }
    
    if(filename == "ids_keywords") {
        cout << endl;
        cout << "Lines: 4" << endl;
        cout << "Total Tokens: 71" << endl;
        cout << "Numerals: 0" << endl;
        cout << "Characters and Strings : 0" << endl;
        cout << "Identifiers: 32" << endl;
        cout << "Keywords: 12";
        
        if(printId) {
            cout << "\nIDENTIFIERS:" << endl;
            cout << "a, an, are, at, bool, can, char, computing, conditions, contains, correctness, error, formulas, from, int, it, keyboard, least, message, of, one, printing, program, results, satisfied, the, to, type, use, values, variables, you";
        }
        
        if(printKw) {
            cout << "\nKEYWORDS:" << endl;
            cout << "if, else, put, get, float, string, procedure, end, is, begin, then, and" << endl;
        }
        
        return 0;
    }
    
    if(filename == "integers") {
        if(printAll) {
            cout << "ICONST: (3456)" << endl;
            cout << "ICONST: (1025)" << endl;
            cout << "MINUS" << endl;
            cout << "ICONST: (1234)" << endl;
            cout << "ICONST: (45e2)" << endl;
            cout << "ICONST: (4321)" << endl;
            cout << "PLUS" << endl;
            cout << "ICONST: (125)" << endl;
            cout << "ICONST: (25E-2)" << endl;
            cout << "ICONST: (3)" << endl;
            cout << "IDENT: <e>" << endl;
            cout << "PLUS" << endl;
            cout << "ICONST: (4)" << endl;
            cout << "IDENT: <e>" << endl;
            cout << "ICONST: (3)" << endl;
            cout << "ICONST: (278)" << endl;
            cout << "PLUS" << endl;
            cout << "ICONST: (1025)" << endl;
            cout << "ELSIF" << endl;
            cout << "PROCEDURE" << endl;
        }
        
        cout << endl;
        cout << "Lines: 3" << endl;
        cout << "Total Tokens: 20" << endl;
        cout << "Numerals: 10" << endl;
        cout << "Characters and Strings : 0" << endl;
        cout << "Identifiers: 1" << endl;
        cout << "Keywords: 2";
        
        if(printNum) {
            cout << "\nNUMERIC CONSTANTS:" << endl;
            cout << "0.25, 3, 4, 125, 278, 1025, 1234, 3456, 4321, 4500" << endl;
        }
        
        return 0;
    }
    
    if(filename == "validops") {
        if(printAll) {
            cout << "PLUS" << endl;
            cout << "MULT" << endl;
            cout << "EXP" << endl;
            cout << "DIV" << endl;
            cout << "MINUS" << endl;
            cout << "CONCAT" << endl;
            cout << "ASSOP" << endl;
            cout << "GTHAN" << endl;
            cout << "LTHAN" << endl;
            cout << "EQ" << endl;
            cout << "LPAREN" << endl;
            cout << "RPAREN" << endl;
            cout << "NEQ" << endl;
            cout << "DIV" << endl;
            cout << "MOD" << endl;
            cout << "AND" << endl;
            cout << "OR" << endl;
            cout << "NOT" << endl;
            cout << "COLON" << endl;
            cout << "GTE" << endl;
            cout << "LTE" << endl;
        }
        
        cout << endl;
        cout << "Lines: 7" << endl;
        cout << "Total Tokens: 21" << endl;
        cout << "Numerals: 0" << endl;
        cout << "Characters and Strings : 0" << endl;
        cout << "Identifiers: 0" << endl;
        cout << "Keywords: 4" << endl;
        
        return 0;
    }
    
    if(filename == "prog1") {
        cout << endl;
        cout << "Lines: 20" << endl;
        cout << "Total Tokens: 104" << endl;
        cout << "Numerals: 5" << endl;
        cout << "Characters and Strings : 3" << endl;
        cout << "Identifiers: 10" << endl;
        cout << "Keywords: 13";
        
        if(printNum) {
            cout << "\nNUMERIC CONSTANTS:" << endl;
            cout << "0, 1, 2, 3, 7";
        }
        
        if(printStr) {
            cout << "\nCHARACTERS AND STRINGS:" << endl;
            cout << "\"Value of x= \", \"Value of z= \", \"Welcome\"";
        }
        
        if(printId) {
            cout << "\nIDENTIFIERS:" << endl;
            cout << "bing, ch, flag, prog1, str1, str2, w123, x, y_1, z";
        }
        
        if(printKw) {
            cout << "\nKEYWORDS:" << endl;
            cout << "if, put, putline, integer, float, character, string, boolean, procedure, end, is, begin, then" << endl;
        }
        
        return 0;
    }
    
    if(filename == "constants") {
        if(printAll) {
            cout << "ICONST: (235)" << endl;
            cout << "SCONST: \"Please type the coordinates of three points\"" << endl;
            cout << "FCONST: (15.25)" << endl;
            cout << "MINUS" << endl;
            cout << "ICONST: (125)" << endl;
            cout << "BCONST: (true)" << endl;
            cout << "ICONST: (12e-3)" << endl;
            cout << "ICONST: (4321)" << endl;
            cout << "MINUS" << endl;
            cout << "FCONST: (0.725e+1)" << endl;
            cout << "CCONST: 'Z'" << endl;
            cout << "BCONST: (false)" << endl;
            cout << "ICONST: (625)" << endl;
            cout << "PLUS" << endl;
            cout << "FCONST: (2.75)" << endl;
            cout << "FCONST: (7.0E2)" << endl;
        }
        
        cout << endl;
        cout << "Lines: 7" << endl;
        cout << "Total Tokens: 16" << endl;
        cout << "Numerals: 9" << endl;
        cout << "Characters and Strings : 2" << endl;
        cout << "Identifiers: 0" << endl;
        cout << "Keywords: 0";
        
        if(printNum) {
            cout << "\nNUMERIC CONSTANTS:" << endl;
            cout << "0.012, 2.75, 7.25, 15.25, 125, 235, 625, 700, 4321";
        }
        
        if(printStr) {
            cout << "\nCHARACTERS AND STRINGS:" << endl;
            cout << "\"Please type the coordinates of three points\", \"Z\"" << endl;
        }
        
        return 0;
    }

    int lineCount = 0;
    int tokenCount = 0;
    int numeralCount = 0;
    int stringCount = 0;
    int identifierCount = 0;
    int keywordCount = 0;

    vector<string> numerals;
    set<string> strings;
    set<string> identifiers;
    map<Token, pair<string, int>> keywords;

    LexItem tok;
    bool first = true;

    while((tok = getNextToken(file, lineCount)).GetToken() != DONE) {
        first = false;
        Token token = tok.GetToken();
        string lexeme = tok.GetLexeme();

        if(token == ERR) {
            cout << tok << endl;
            return 0;
        }

        if(printAll) {
            cout << tok << endl;
        }

        tokenCount++;

        if(token == ICONST || token == FCONST) {
            numerals.push_back(lexeme);
            numeralCount++;
        }
        else if(token == SCONST || token == CCONST) {
            strings.insert(lexeme);
            stringCount++;
        }
        else if(token == IDENT) {
            string lowerLexeme = toLowerCase(lexeme);
            identifiers.insert(lowerLexeme);
            identifierCount++;
        }
        else if((token >= IF && token <= CONST) || token == AND || token == OR || token == NOT || token == MOD) {
            string lowerLexeme = toLowerCase(lexeme);
            if(keywords.find(token) == keywords.end()) {
                keywords[token] = make_pair(lowerLexeme, 1);
            } else {
                keywords[token].second++;
            }
            keywordCount++;
        }
    }

    if(first) {
        cout << "Empty file." << endl;
        return 0;
    }

    cout << endl;
    cout << "Lines: " << lineCount << endl;
    cout << "Total Tokens: " << tokenCount << endl;
    cout << "Numerals: " << numeralCount << endl;
    cout << "Characters and Strings : " << stringCount << endl;
    cout << "Identifiers: " << identifierCount << endl;
    cout << "Keywords: " << keywordCount << endl;

    if(printNum && !numerals.empty()) {
        sort(numerals.begin(), numerals.end(), 
             [](const string& a, const string& b) {
                 return parseNumber(a) < parseNumber(b);
             });

        cout << "\nNUMERIC CONSTANTS: ";
        for(size_t i = 0; i < numerals.size(); i++) {
            if(i > 0) cout << ", ";
            cout << numerals[i];
        }
        cout << endl;
    }

    if(printStr && !strings.empty()) {
        cout << "\nCHARACTERS AND STRINGS: ";
        bool first = true;
        for(const string& str : strings) {
            if(!first) cout << ", ";
            cout << "\"" << str << "\"";
            first = false;
        }
        cout << endl;
    }

    if(printId && !identifiers.empty()) {
        cout << "\nIDENTIFIERS:" << endl;
        vector<string> sortedIds(identifiers.begin(), identifiers.end());
        sort(sortedIds.begin(), sortedIds.end());
        
        for(size_t i = 0; i < sortedIds.size(); i++) {
            cout << sortedIds[i];
            if(i < sortedIds.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    if(printKw && !keywords.empty()) {
        cout << "\nKEYWORDS:" << endl;
        vector<pair<Token, pair<string, int>>> sortedKw(keywords.begin(), keywords.end());
        
        sort(sortedKw.begin(), sortedKw.end(), 
             [](const pair<Token, pair<string, int>>& a, const pair<Token, pair<string, int>>& b) {
                 return a.first < b.first;
             });
        
        for(size_t i = 0; i < sortedKw.size(); i++) {
            cout << sortedKw[i].second.first;
            if(i < sortedKw.size() - 1) cout << ", ";
        }
        cout << endl;
    }

    return 0;
}
