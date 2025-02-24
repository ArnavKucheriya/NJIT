#include "lex.h"
#include <ctype.h>
#include <algorithm>

Token token;

LexItem getNextToken(istream& in, int& linenum) {
    enum TokState {START, ININT, INREAL, INID, INSTRING} lexstate = START;
    string lexeme;
    string testLexeme;
    char ch;
    string line;
    char peek;
    
    while(in.get(ch)) {
        switch(lexstate) {
        case START:
            lexeme = ch;
            if (ch == '\n' || ch == '\r') {
                linenum++;
                break;
            }
            else if (ch == '#') {               
                getline(in, line);
                linenum++;
                break;
            }
            else if (ch == ' ' || ch == '\t') {
                break;
            }
            else if (ch == '@' || ch == '$' || isalpha(ch) || ch == '_') {
                lexstate = INID;
                break;
            }
            else if (isdigit(ch)) {
                lexstate = ININT;
                break;
            }
            else if (ch == '\'') {
                lexstate = INSTRING;
                break;
            }
            else if (ch == '+') {
                return LexItem(PLUS, lexeme, linenum);
            }
            else if (ch == '&') {
                return LexItem(CONCAT, lexeme, linenum);
            }            
            else if (ch == ':') {
                return LexItem(COLON, lexeme, linenum);
            }
            
            else if (ch == '-') {
                peek = in.peek();  // Look at the next character
            
                if (isdigit(peek)) {  // If `-` is followed by a number, it's part of a numeric constant
                    lexeme += in.get();  // Consume the digit
                    lexstate = ININT;  // Switch state to process an integer
                } 
                else {  // If it's not a number, it's a standalone MINUS token
                    return LexItem(MINUS, lexeme, linenum);
                }
            }
            else if (ch == '*') {
                peek = in.peek();
                if (peek == '*') {
                    lexeme = (ch + peek); // "**"
                    in.get();
                    return LexItem(EXP, lexeme, linenum);
                }
                return LexItem(MULT, lexeme, linenum);
            }
            else if (ch == '/') {
                return LexItem(DIV, lexeme, linenum);
            }
            else if (ch == '^') {
                return LexItem(EXP, lexeme, linenum);
            }
            else if (ch == '=') {
                peek = in.peek();
                if (peek == '=') {
                    lexeme = (ch + peek); // "=="
                    in.get();
                    return LexItem(NEQ, lexeme, linenum);
                }
                return LexItem(ASSOP, lexeme, linenum);
            }
            else if (ch == '(') {
                return LexItem(LPAREN, lexeme, linenum);
            }
            else if (ch == ')') {
                return LexItem(RPAREN, lexeme, linenum);
            }
            else if (ch == '>') {
                return LexItem(GTE, lexeme, linenum);
            }
            else if (ch == '<') {
                return LexItem(LTE, lexeme, linenum);
            }
            else if (ch == '.') {
                return LexItem(CONCAT, lexeme, linenum);
            }
            else if (ch == ',') {
                return LexItem(COMMA, lexeme, linenum);
            }
            else if (ch == ';') {
                return LexItem(SEMICOL, lexeme, linenum);
            }
            //break;
            return LexItem(ERR, lexeme, linenum);
        case ININT:
            if (isdigit(ch)) {
                    lexeme += ch;
            }
            else if (ch == '.') {
                lexeme += ch;
                lexstate = INREAL;
                break;
            }
            else {
                in.putback(ch);
                return LexItem(ICONST, lexeme, linenum);
            }
            while(in.get(ch)) {
                if (isdigit(ch)) {
                    lexeme += ch;
                }
                else if (ch == '.') {
                    lexeme += ch;
                    lexstate = INREAL;
                    break;
                }
                else {
                    in.putback(ch);
                    return LexItem(ICONST, lexeme, linenum);
                }
            }
            break;
        case INREAL:
            if (isdigit(ch)) {
                    lexeme += ch;
            }
            else if (ch == '.') {
                lexeme += ch;                
                return LexItem(ERR, lexeme, linenum);
            }
            else {
                in.putback(ch);
                return LexItem(FCONST, lexeme, linenum);
            }
            while(in.get(ch)) {
                if (isdigit(ch)) {
                    lexeme += ch;
                }
                else if (ch == '.') {
                    lexeme += ch;                
                    return LexItem(ERR, lexeme, linenum);
                }
                else {
                    in.putback(ch);
                    return LexItem(FCONST, lexeme, linenum);
                }
            }
            break;
            case INID:
            if (isalnum(ch) || ch == '_') {
                lexeme += ch;
            } else {
                in.putback(ch);
                if (isdigit(lexeme[0]))  // If it starts with a digit, it's a mistake
                    return LexItem(ERR, lexeme, linenum);
                return id_or_kw(lexeme, linenum);
            }
        
            break;     
        case INSTRING:
            if (ch != '\n') {
                lexeme += ch;
            }
            if (ch == '\'') {
                return LexItem(SCONST, lexeme, linenum);
            }
            else if (ch == '\n') {
                return LexItem(ERR, lexeme, linenum);
            }
            while(in.get(ch)) {
                if (ch != '\n') {
                    lexeme += ch;
                }
                if (ch == '\'') {
                    lexeme.erase(remove(lexeme.begin(), lexeme.end(), '\''), lexeme.end()); //remove ' from string
                    return LexItem(SCONST, lexeme, linenum);
                }
                else if (ch == '\n') {
                    return LexItem(ERR, lexeme, linenum);
                }
            }
            break;
        // Insert here if more states are needed
        }
        
    }
    return LexItem(DONE, lexeme, linenum);
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    Token token;

    if (lexeme[0] == '@') {
        token = IDENT;
    } 
    else if (lexeme[0] == '$') {
        token = IDENT;
    }
    else {
        token = IDENT;
    }

    map<string, Token> maps = {
        {"PUTLN", PUTLN}, {"if", IF}, {"else", ELSE}
    };
    map<string, Token>::iterator it;
    for(it = maps.begin(); it != maps.end(); it++) {
        if (maps.count(lexeme) > 0)
            return LexItem(maps[lexeme], lexeme, linenum);
    }
    return LexItem(token, lexeme, linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok) {
    int line;
    line = tok.GetLinenum();
    Token toks = tok.GetToken();
    string lexeme = tok.GetLexeme();

    switch(toks) {
        // Keywords
        case PUTLN:
            return out << "PUTLN" << endl;
            break;
        case IF:
            return out << "IF" << endl;
            break;
        case ELSE:
            return out << "IDENT(" << lexeme << ")" << endl;
            break;
        // Identifiers
        case IDENT:
            return out << "IDENT(" << lexeme << ")" << endl;
            break;
        // Constants
        case ICONST:
            return out << "ICONST(" << lexeme << ")" << endl;            
            break;
        case FCONST:
            return out << "FCONST(" << lexeme << ")" << endl;            
            break;
        case SCONST:
            return out << "SCONST(" << lexeme << ")" << endl;            
            break;
        // Operators
        case PLUS:
            return out << "PLUS" << endl;
            break;
        case MINUS:
            return out << "MINUS" << endl;
            break;
        case MULT:
            return out << "MULT" << endl;
            break;
        case DIV:
            return out << "DIV" << endl;
            break;
        case EXP:
            return out << "EXP" << endl;
            break;
        case ASSOP:
            return out << "ASSOP" << endl;
            break;
        case NEQ:
            return out << "NEQ" << endl;
            break;
        case GTE:
            return out << "GTE" << endl;
            break;
        case LTE:
            return out << "LTE" << endl;
            break;
        case CONCAT:
            return out << "CONCAT" << endl;
            break;
        case EQ:
            return out << "EQ" << endl;
            break;
        case GTHAN:
            return out << "GTHAN" << endl;
            break;
        case LTHAN:
            return out << "LTHAN" << endl;
            break;
        // Keyword tokens
        case COMMA:
            return out << "COMMA" << endl;
            break;
        case LPAREN:
            return out << "LPAREN" << endl;
            break;
        case RPAREN:
            return out << "RPAREN" << endl;
            break;
        case SEMICOL:
            return out << "SEMICOL" << endl;
            break;
        case ELSIF:
            return out << "ELSIF" << endl;
            break;
        case PUT:
            return out << "PUT" << endl;
            break;
        case GET:
            return out << "GET" << endl;
            break;
        case INT:
            return out << "INT" << endl;
            break;
        case FLOAT:
            return out << "FLOAT" << endl;
            break;
        case CHAR:
            return out << "CHAR" << endl;
            break;
        case STRING:
            return out << "STRING" << endl;
            break;
        case BOOL:
            return out << "BOOL" << endl;
            break;
        case PROCEDURE:
            return out << "PROCEDURE" << endl;
            break;
        case TRUE:
            return out << "TRUE" << endl;
            break;
        case FALSE:
            return out << "FALSE" << endl;
            break;
        case END:
            return out << "END" << endl;
            break;
        case IS:
            return out << "IS" << endl;
            break;
        case BEGIN:
            return out << "BEGIN" << endl;
            break;
        case THEN:
            return out << "THEN" << endl;
            break;
        case CONST:
            return out << "CONST" << endl;
            break;
        case MOD:
            return out << "MOD" << endl;
            break;
        case AND:
            return out << "AND" << endl;
            break;
        case OR:
            return out << "OR" << endl;
            break;
        case NOT:
            return out << "NOT" << endl;
            break;
        case DOT:
            return out << "DOT" << endl;
            break;
        case COLON:
            return out << "COLON" << endl;
            break;
        case BCONST:
            return out << "BCONST" << endl;
            break;
        case CCONST:
            return out << "CCONST" << endl;
            break;
        // ERR
        case ERR:
            return out << "Error in line " << line+1 << " (" << lexeme << ")" << endl;
            break;
        // DONE
        case DONE:
            return out << "DONE" << endl;
            break;
    }
    return out << endl;
}