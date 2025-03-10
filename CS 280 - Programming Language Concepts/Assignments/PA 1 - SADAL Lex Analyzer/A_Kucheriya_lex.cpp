#include <cctype>
#include <map>
#include <string>
#include "lex.h"

using namespace std;

static map<string, Token> keywordDict = {
    {"procedure", PROCEDURE},
    {"if", IF},
    {"else", ELSE},
    {"elsif", ELSIF},
    {"put", PUT},
    {"putline", PUTLN},
    {"get", GET},
    {"integer", INT},
    {"float", FLOAT},
    {"character", CHAR},
    {"string", STRING},
    {"boolean", BOOL},
    {"true", TRUE},
    {"false", FALSE},
    {"end", END},
    {"is", IS},
    {"begin", BEGIN},
    {"then", THEN},
    {"constant", CONST},
    {"mod", MOD},
    {"and", AND},
    {"or", OR},
    {"not", NOT}
};

static string toLower(const string& str) {
    string result = str;
    for(char& c : result) {
        c = tolower(c);
    }
    return result;
}

LexItem id_or_kw(const string& lexeme, int linenum) {
    string lowerLexeme = toLower(lexeme);
    auto it = keywordDict.find(lowerLexeme);
    if(it != keywordDict.end()) {
        if(it->second == TRUE || it->second == FALSE)
            return LexItem(BCONST, lowerLexeme, linenum);
        return LexItem(it->second, lowerLexeme, linenum);
    }
    return LexItem(IDENT, lowerLexeme, linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok) {
    Token token = tok.GetToken();
    string lexeme = tok.GetLexeme();
    int line = tok.GetLinenum();

    if(token == ERR) {
        out << "ERR: In line " << line << ", Error Message {" << lexeme << "}";
        return out;
    }

    switch(token) {
        case IDENT:
            out << "IDENT: <" << lexeme << ">";
            break;
        case ICONST:
            out << "ICONST: (" << lexeme << ")";
            break;
        case FCONST:
            out << "FCONST: (" << lexeme << ")";
            break;
        case SCONST:
            out << "SCONST: \"" << lexeme << "\"";
            break;
        case CCONST:
            out << "CCONST: '" << lexeme << "'";
            break;
        case BCONST:
            out << "BCONST: (" << lexeme << ")";
            break;
        case PLUS: out << "PLUS"; 
        break;
        case MINUS: out << "MINUS"; 
        break;
        case MULT: out << "MULT"; 
        break;
        case DIV: out << "DIV"; 
        break;
        case COMMA: out << "COMMA";
        break;
        case DOT: out << "DOT"; 
        break;
        case COLON: out << "COLON"; 
        break;
        case ASSOP: out << "ASSOP"; 
        break;
        case LPAREN: out << "LPAREN"; 
        break;
        case RPAREN: out << "RPAREN"; 
        break;
        case SEMICOL: out << "SEMICOL"; 
        break;
        case IF: out << "IF"; 
        break;
        case ELSE: out << "ELSE"; 
        break;
        case ELSIF: out << "ELSIF"; 
        break;
        case INT: out << "INT"; 
        break;
        case FLOAT: out << "FLOAT"; 
        break;
        case BOOL: out << "BOOL"; 
        break;
        case PROCEDURE: out << "PROCEDURE"; 
        break;
        case END: out << "END"; 
        break;
        case BEGIN: out << "BEGIN"; 
        break;
        case CHAR: out << "CHAR"; 
        break;
        case STRING: out << "STRING"; 
        break;
        case CONST: out << "CONST"; 
        break;
        case AND: out << "AND"; 
        break;
        case OR: out << "OR"; 
        break;
        case NOT: out << "NOT"; 
        break;
        case THEN: out << "THEN"; 
        break;
        case MOD: out << "MOD"; 
        break;
        case EQ: out << "EQ"; 
        break;
        case NEQ: out << "NEQ"; 
        break;
        case GTHAN: out << "GTHAN"; 
        break;
        case LTHAN: out << "LTHAN"; 
        break;
        case GTE: out << "GTE"; 
        break;
        case LTE: out << "LTE"; 
        break;
        case CONCAT: out << "CONCAT"; 
        break;
        case EXP: out << "EXP"; 
        break;
        default:
            out << token;
    }
    return out;
}

LexItem getNextToken(istream& in, int& linenum) {
    enum State { START, INID, INSTRING, INCHAR, ININT, INFLOAT, INEXPONENT };
    State state = START;
    string lexeme;
    char ch;
    bool prev_underscore = false;
    bool exponent_sign_allowed = false;

    if(linenum == 0) linenum = 1;

    while(in.get(ch)) {
        switch(state) {
            case START:
                if(isspace(ch)) {
                    if(ch == '\n') {
                        linenum++;
                    }
                    continue;
                }

                lexeme = "";

                if(ch == '-') {
                    char next = in.peek();
                    if(next == '-') {
                        in.get();
                        
                        while(in.get(ch)) {
                            if(ch == '\n') {
                                linenum++;
                                break;
                            }
                        }
                        
                        if(in.eof()) {
                            return LexItem(DONE, "", linenum);
                        }
                        
                        continue;
                    }
                    return LexItem(MINUS, "-", linenum);
                }

                if(ch == '_') {
                    return LexItem(ERR, "_", linenum);
                }

                if(ch == '"') {
                    state = INSTRING;
                    continue;
                }

                if(ch == '\'') {
                    state = INCHAR;
                    continue;
                }

                if(isalpha(ch)) {
                    lexeme = ch;
                    state = INID;
                    prev_underscore = false;
                    continue;
                }

                if(isdigit(ch)) {
                    lexeme = ch;
                    state = ININT;
                    continue;
                }

                switch(ch) {
                    case ',': return LexItem(COMMA, ",", linenum);
                    case '.': return LexItem(DOT, ".", linenum);
                    case '+': return LexItem(PLUS, "+", linenum);
                    case '*': 
                        if(in.peek() == '*') {
                            in.get();
                            return LexItem(EXP, "**", linenum);
                        }
                        return LexItem(MULT, "*", linenum);
                    case '/': 
                        if(in.peek() == '=') {
                            in.get();
                            return LexItem(NEQ, "/=", linenum);
                        }
                        return LexItem(DIV, "/", linenum);
                    case '=': return LexItem(EQ, "=", linenum);
                    case '(': return LexItem(LPAREN, "(", linenum);
                    case ')': return LexItem(RPAREN, ")", linenum);
                    case ';': return LexItem(SEMICOL, ";", linenum);
                    case ':':
                        if(in.peek() == '=') {
                            in.get();
                            return LexItem(ASSOP, ":=", linenum);
                        }
                        return LexItem(COLON, ":", linenum);
                    case '<':
                        if(in.peek() == '=') {
                            in.get();
                            return LexItem(LTE, "<=", linenum);
                        }
                        return LexItem(LTHAN, "<", linenum);
                    case '>':
                        if(in.peek() == '=') {
                            in.get();
                            return LexItem(GTE, ">=", linenum);
                        }
                        return LexItem(GTHAN, ">", linenum);
                    case '&':
                        return LexItem(CONCAT, "&", linenum);
                    default:
                        return LexItem(ERR, string(1, ch), linenum);
                }

            case INID:
                if(isalnum(ch) || ch == '_') {
                    if(ch == '_') {
                        if(prev_underscore) {
                            if(!lexeme.empty()) {
                                in.putback(ch);
                                return id_or_kw(lexeme, linenum);
                            }
                            return LexItem(ERR, "_", linenum);
                        }
                        prev_underscore = true;
                    } else {
                        prev_underscore = false;
                    }
                    lexeme += ch;
                }
                else {
                    if(isspace(ch)) {
                        if(ch == '\n') linenum++;
                    } else {
                        in.putback(ch);
                    }
                    return id_or_kw(lexeme, linenum);
                }
                break;

            case INSTRING:
                if(ch == '\n') {
                    return LexItem(ERR, " Invalid string constant \"" + lexeme, linenum);
                }
                if(ch == '"') {
                    return LexItem(SCONST, lexeme, linenum);
                }
                lexeme += ch;
                break;

            case INCHAR:
                if(ch == '\n') {
                    return LexItem(ERR, "New line is an invalid character constant.", linenum);
                }
                if(ch == '\'') {
                    if(lexeme.length() > 1) {
                        return LexItem(ERR, " Invalid character constant '" + lexeme.substr(0,2) + "'", linenum);
                    }
                    return LexItem(CCONST, lexeme, linenum);
                }
                lexeme += ch;
                break;

            case ININT:
                if(isdigit(ch)) {
                    lexeme += ch;
                }
                else if(ch == '.') {
                    lexeme += ch;
                    state = INFLOAT;
                }
                else if(ch == 'E' || ch == 'e') {
                    if(in.peek() == '+' || in.peek() == '-' || isdigit(in.peek())) {
                        lexeme += ch;
                        state = INEXPONENT;
                        exponent_sign_allowed = true;
                    } else {
                        in.putback(ch);
                        return LexItem(ICONST, lexeme, linenum);
                    }
                }
                else {
                    in.putback(ch);
                    return LexItem(ICONST, lexeme, linenum);
                }
                break;

            case INFLOAT:
                if(isdigit(ch)) {
                    lexeme += ch;
                }
                else if((ch == 'E' || ch == 'e') && lexeme[lexeme.length()-1] != '.') {
                    if(in.peek() == '+' || in.peek() == '-' || isdigit(in.peek())) {
                        lexeme += ch;
                        state = INEXPONENT;
                        exponent_sign_allowed = true;
                    } else {
                        in.putback(ch);
                        return LexItem(FCONST, lexeme, linenum);
                    }
                }
                else if(ch == '.') {
                    return LexItem(ERR, lexeme + ".", linenum);
                }
                else {
                    if(lexeme[lexeme.length()-1] == '.') {
                        return LexItem(ERR, lexeme, linenum);
                    }
                    in.putback(ch);
                    return LexItem(FCONST, lexeme, linenum);
                }
                break;

            case INEXPONENT:
                if(isdigit(ch)) {
                    lexeme += ch;
                    exponent_sign_allowed = false;
                }
                else if((ch == '+' || ch == '-') && exponent_sign_allowed) {
                    lexeme += ch;
                    exponent_sign_allowed = false;
                }
                else {
                    if(!isdigit(lexeme[lexeme.length()-1])) {
                        string number = lexeme.substr(0, lexeme.length()-1);
                        in.putback(lexeme[lexeme.length()-1]);
                        if(number.find('.') != string::npos) {
                            return LexItem(FCONST, number, linenum);
                        }
                        return LexItem(ICONST, number, linenum);
                    }
                    in.putback(ch);
                    return LexItem(FCONST, lexeme, linenum);
                }
                break;
        }
    }

    if(!lexeme.empty()) {
        switch(state) {
            case INID:
                return id_or_kw(lexeme, linenum);
            case ININT:
                return LexItem(ICONST, lexeme, linenum);
            case INFLOAT:
                if(lexeme[lexeme.length()-1] == '.') {
                    return LexItem(ERR, lexeme, linenum);
                }
                return LexItem(FCONST, lexeme, linenum);
            case INSTRING:
                return LexItem(ERR, " Invalid string constant \"" + lexeme, linenum);
            case INCHAR:
                return LexItem(ERR, "New line is an invalid character constant.", linenum);
            default:
                break;
        }
    }

    return LexItem(DONE, "", linenum);
}
