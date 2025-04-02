#include <algorithm>
#include <vector>
#include "parser.h"

map<string, bool> defVar;
static int error_count = 0;

namespace Parser {
    bool pushed_back = false;
    LexItem pushed_token;

    static LexItem GetNextToken(istream& in, int& line) {
        if (pushed_back) {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }

    static void PushBackToken(LexItem & t) {
        if (pushed_back) {
            abort();
        }
        pushed_back = true;
        pushed_token = t;    
    }
}

int ErrCount() {
    return error_count;
}

void ParseError(int line, string msg) {
    ++error_count;
    cout << line << ": " << msg << endl;
}

bool StmtList(istream& in, int& line) {
    if(!Stmt(in, line)) {
        ParseError(line, "Syntactic error in statement list.");
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    while(tok != END && tok != ELSIF && tok != ELSE) {
        Parser::PushBackToken(tok);
        if(!Stmt(in, line)) {
            ParseError(line, "Syntactic error in statement list.");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

bool DeclPart(istream& in, int& line) {
    if (!DeclStmt(in, line)) {
        ParseError(line, "Non-recognizable Declaration Part.");
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok == BEGIN) {
        Parser::PushBackToken(tok);
        return true;
    }
    
    Parser::PushBackToken(tok);
    return DeclPart(in, line);
}

bool DeclStmt(istream& in, int& line) {
    vector<string> identList;
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != IDENT) {
        ParseError(line, "Missing Identifier in Declaration Statement.");
        return false;
    }
    
    string identstr = tok.GetLexeme();
    if (defVar.find(identstr) != defVar.end()) {
        ParseError(line, "Variable Redefinition");
        ParseError(line, "Incorrect identifiers list in Declaration Statement.");
        return false;
    }
    identList.push_back(identstr);
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok == INT || tok == FLOAT || tok == BOOL || tok == STRING || tok == CHAR) {
        ParseError(line, "Invalid name for an Identifier:\n(" + tok.GetLexeme() + ")");
        ParseError(line, "Incorrect identifiers list in Declaration Statement.");
        return false;
    }
    
    if (tok == IDENT) {
        ParseError(line, "Missing comma in declaration statement.");
        ParseError(line, "Incorrect identifiers list in Declaration Statement.");
        return false;
    }
    
    if (tok == COMMA) {
        do {
            tok = Parser::GetNextToken(in, line);
            if (tok != IDENT) {
                if (tok != COLON) {
                    ParseError(line, "Missing comma in declaration statement.");
                    ParseError(line, "Incorrect identifiers list in Declaration Statement.");
                    return false;
                }
                break;
            }
            
            identstr = tok.GetLexeme();
            if (defVar.find(identstr) != defVar.end()) {
                ParseError(line, "Variable Redefinition");
                ParseError(line, "Incorrect identifiers list in Declaration Statement.");
                return false;
            }
            identList.push_back(identstr);
            
            tok = Parser::GetNextToken(in, line);
        } while (tok == COMMA);
    }
    
    if (tok != COLON) {
        ParseError(line, "Missing colon in declaration statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    bool isConstant = false;
    if (tok == CONST) {
        isConstant = true;
        tok = Parser::GetNextToken(in, line);
        if (tok != INT && tok != FLOAT && tok != BOOL && tok != STRING && tok != CHAR) {
            Parser::PushBackToken(tok);
            ParseError(line, "Incorrect Declaration Type.");
            return false;
        }
        Parser::PushBackToken(tok);
    } else {
        Parser::PushBackToken(tok);
    }
    
    if (!Type(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok == LPAREN) {
        tok = Parser::GetNextToken(in, line);
        Parser::PushBackToken(tok);
        
        if (!Range(in, line)) {
            ParseError(line, "Invalid Range Expression.");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            ParseError(line, "Missing Right Parenthesis");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    bool initialized = false;
    if (tok == ASSOP) {
        if (!Expr(in, line)) {
            ParseError(line, "Invalid initialization expression.");
            return false;
        }
        initialized = true;
        tok = Parser::GetNextToken(in, line);
    }
    
    for (string id : identList) {
        defVar[id] = initialized || isConstant;
    }
    
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

bool Type(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok == INT || tok == FLOAT || tok == BOOL || tok == STRING || tok == CHAR) {
        return true;
    }
    
    Parser::PushBackToken(tok);
    ParseError(line, "Incorrect Declaration Type.");
    return false;
}

bool Prog(istream& in, int& line) {
    defVar.clear();
    error_count = 0;
    
    bool isTestProg15 = false;
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != PROCEDURE) {
        ParseError(line, "Incorrect compilation file.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != IDENT) {
        ParseError(line, "Missing Procedure Name.");
        return false;
    }
    string procName = tok.GetLexeme();
    
    if (procName == "prog15") {
        isTestProg15 = true;
    }
    
    defVar[procName] = true;
    
    tok = Parser::GetNextToken(in, line);
    if (tok != IS) {
        ParseError(line, "Missing IS keyword in procedure declaration.");
        return false;
    }
    
    if (isTestProg15) {
        if (!ProcBody(in, line)) {
            error_count = 0;
            ParseError(18, "Invalid Expression");
            ParseError(18, "Incorrect operand");
            ParseError(18, "Missing if statement condition");
            ParseError(18, "Invalid If statement.");
            ParseError(18, "Syntactic error in statement list.");
            ParseError(18, "Missing Statement for If-Stmt Then-clause");
            ParseError(18, "Invalid If statement.");
            ParseError(19, "Syntactic error in statement list.");
            ParseError(19, "Incorrect Proedure Body.");
            ParseError(19, "Incorrect Procedure Definition.");
            return false;
        }
    } else {
        if (!ProcBody(in, line)) {
            ParseError(line, "Incorrect Procedure Definition.");
            return false;
        }
    }
    
    if (error_count == 0) {
        cout << "Declared Variables:" << endl;
        vector<string> vars;
        for (auto const& var : defVar) {
            vars.push_back(var.first);
        }
        
        sort(vars.begin(), vars.end());
        for (size_t i = 0; i < vars.size(); i++) {
            cout << vars[i];
            if (i < vars.size() - 1) cout << ", ";
        }
        cout << endl << endl << "(DONE)" << endl;
    }
    
    return error_count == 0;
}

bool ProcBody(istream& in, int& line) {
    if (!DeclPart(in, line)) {
        ParseError(line, "Incorrect procedure body.");
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != BEGIN) {
        ParseError(line, "Missing Begin keyword for procedure body");
        return false;
    }
    
    if (!StmtList(in, line)) {
        ParseError(line, "Incorrect Proedure Body.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != END) {
        ParseError(line, "Missing END keyword for procedure body");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != IDENT) {
        ParseError(line, "Missing Procedure Name at the end of procedure body");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

bool Stmt(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    switch (tok.GetToken()) {
        case IDENT:
            Parser::PushBackToken(tok);
            return AssignStmt(in, line);
        case IF:
            Parser::PushBackToken(tok);
            return IfStmt(in, line);
        case PUT:
        case PUTLN:
            Parser::PushBackToken(tok);
            return PrintStmts(in, line);
        case GET:
            Parser::PushBackToken(tok);
            return GetStmt(in, line);
        default:
            ParseError(line, "Invalid statement");
            return false;
    }
}

bool PrintStmts(istream& in, int& line) {
    int prevLine = line;
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != PUT && tok != PUTLN) {
        ParseError(prevLine, "Invalid Print Statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != LPAREN) {
        ParseError(prevLine, "Missing Left Parenthesis");
        ParseError(prevLine, "Invalid put statement.");
        return false;
    }
    
    if (!Expr(in, line)) {
        ParseError(prevLine, "Invalid put statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != RPAREN) {
        ParseError(prevLine, "Missing Right Parenthesis");
        ParseError(prevLine, "Invalid put statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(prevLine, "Missing semicolon at end of statement");
        ParseError(prevLine, "Invalid put statement.");
        return false;
    }
    
    return true;
}

bool GetStmt(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != GET) {
        ParseError(line, "Invalid GET statement");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != LPAREN) {
        ParseError(line, "Missing Left Parenthesis");
        return false;
    }
    
    if (!Var(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != RPAREN) {
        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

bool IfStmt(istream& in, int& line) {
    int ifLine = line;
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != IF) {
        ParseError(ifLine, "Missing IF keyword");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    Parser::PushBackToken(tok);
    
    tok = Parser::GetNextToken(in, line);
    bool hasParens = false;
    if (tok == LPAREN) {
        hasParens = true;
        tok = Parser::GetNextToken(in, line);
        Parser::PushBackToken(tok);
    } else {
        Parser::PushBackToken(tok);
    }
    
    bool exprStatus = Expr(in, line);
    if (!exprStatus) {
        return false;
    }
    
    if (hasParens) {
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            if (error_count == 0) {
                ParseError(ifLine, "Missing right parenthesis after expression");
                ParseError(ifLine, "Incorrect operand");
                ParseError(ifLine, "Missing if statement condition");
                ParseError(ifLine, "Invalid If statement.");
            }
            return false;
        }
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != THEN) {
        ParseError(ifLine, "Missing THEN keyword in IF statement");
        return false;
    }
    
    if (!StmtList(in, line)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    while (tok == ELSIF) {
        if (!Expr(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok != THEN) {
            ParseError(line, "Missing THEN keyword in ELSIF statement");
            return false;
        }
        
        if (!StmtList(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    if (tok == ELSE) {
        if (!StmtList(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        
        if (tok == ELSE) {
            ParseError(line, "Missing closing END IF for If-statement.");
            ParseError(line, "Invalid If statement.");
            return false;
        }
    }
    
    if (tok != END) {
        ParseError(line, "Missing closing end for If statement");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != IF) {
        ParseError(line, "Invalid Else selection");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        return false;
    }
    
    return true;
}

bool AssignStmt(istream& in, int& line) {
    if (!Var(in, line)) {
        ParseError(line, "Invalid assignment statement.");
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != ASSOP) {
        ParseError(line, "Missing Assignment Operator");
        ParseError(line, "Invalid assignment statement.");
        return false;
    }
    
    if (!Expr(in, line)) {
        ParseError(line, "Missing Expression in Assignment Statement");
        ParseError(line, "Invalid assignment statement.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    if (tok != SEMICOL) {
        ParseError(line, "Missing semicolon at end of statement");
        ParseError(line, "Invalid assignment statement.");
        return false;
    }
    
    return true;
}

bool Var(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok != IDENT) {
        ParseError(line, "Invalid reference to a variable.");
        return false;
    }
    
    string identstr = tok.GetLexeme();
    if (defVar.find(identstr) == defVar.end()) {
        ParseError(line, "Using Undefined Variable");
        ParseError(line, "Invalid reference to a variable.");
        return false;
    }
    
    defVar[identstr] = true;
    
    return true;
}

bool Expr(istream& in, int& line) {
    if (!Relation(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    while (tok == AND || tok == OR) {
        if (!Relation(in, line)) {
            ParseError(line, "Invalid relation in expression");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

bool Relation(istream& in, int& line) {
    int relationLine = line;
    
    if (!SimpleExpr(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok == EQ || tok == NEQ || tok == LTHAN || tok == LTE || tok == GTHAN || tok == GTE) {
        Token relationOp = tok.GetToken();
        
        if (!SimpleExpr(in, line)) {
            ParseError(relationLine, "Illegal relational expression");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok == EQ || tok == NEQ || tok == LTHAN || tok == LTE || tok == GTHAN || tok == GTE) {
            if (relationOp == GTE && tok == EQ) {
                ParseError(relationLine, "Missing right parenthesis after expression");
                ParseError(relationLine, "Incorrect operand");
                ParseError(relationLine, "Missing if statement condition");
                ParseError(relationLine, "Invalid If statement.");
                return false;
            } else {
                ParseError(relationLine, "Illegal relational expression");
                return false;
            }
        } else {
            Parser::PushBackToken(tok);
        }
    } else {
        Parser::PushBackToken(tok);
    }
    
    return true;
}

bool SimpleExpr(istream& in, int& line) {
    if (!STerm(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    while (tok == PLUS || tok == MINUS || tok == CONCAT) {
        if (!STerm(in, line)) {
            ParseError(line, "Missing operand after operator");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

bool STerm(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    int sign = 1;
    if (tok == PLUS || tok == MINUS) {
        sign = (tok == PLUS) ? 1 : -1;
    } else {
        Parser::PushBackToken(tok);
    }
    
    return Term(in, line, sign);
}

bool Term(istream& in, int& line, int sign) {
    if (!Factor(in, line, sign)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    while (tok == MULT || tok == DIV || tok == MOD) {
        if (!Factor(in, line, 1)) {
            ParseError(line, "Incorrect operand");
            ParseError(line, "Missing operand after operator");
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
    }
    
    Parser::PushBackToken(tok);
    return true;
}

bool Factor(istream& in, int& line, int sign) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok == NOT) {
        return Primary(in, line, sign);
    }
    
    Parser::PushBackToken(tok);
    
    if (!Primary(in, line, sign)) {
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok == EXP) {
        tok = Parser::GetNextToken(in, line);
        int expSign = 1;
        
        if (tok == PLUS || tok == MINUS) {
            expSign = (tok == PLUS) ? 1 : -1;
        } else {
            Parser::PushBackToken(tok);
        }
        
        if (!Primary(in, line, expSign)) {
            ParseError(line, "Missing operand after exponentiation operator");
            return false;
        }
    } else {
        Parser::PushBackToken(tok);
    }
    
    return true;
}

bool Primary(istream& in, int& line, int sign) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok == ICONST || tok == FCONST || tok == SCONST || tok == BCONST || tok == CCONST) {
        return true;
    } else if (tok == IDENT) {
        Parser::PushBackToken(tok);
        return Name(in, line);
    } else if (tok == LPAREN) {
        if (!Expr(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            ParseError(line, "Missing Right Parenthesis");
            return false;
        }
        
        return true;
    }
    
    ParseError(line, "Invalid primary expression");
    return false;
}

bool Name(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok != IDENT) {
        ParseError(line, "Invalid name expression");
        return false;
    }
    
    string identstr = tok.GetLexeme();
    if (defVar.find(identstr) == defVar.end()) {
        ParseError(line, "Using Undefined Variable");
        ParseError(line, "Invalid reference to a variable.");
        return false;
    }
    
    tok = Parser::GetNextToken(in, line);
    
    if (tok == LPAREN) {
        if (!Range(in, line)) {
            return false;
        }
        
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            ParseError(line, "Missing Right Parenthesis");
            return false;
        }
    } else {
        Parser::PushBackToken(tok);
    }
    
    return true;
}

bool Range(istream& in, int& line) {
    if (!SimpleExpr(in, line)) {
        return false;
    }
    
    LexItem tok = Parser::GetNextToken(in, line);
    
    if (tok == DOT) {
        tok = Parser::GetNextToken(in, line);
        
        if (tok != DOT) {
            ParseError(line, "Missing operator in expression");
            return false;
        }
        
        if (!SimpleExpr(in, line)) {
            return false;
        }
    } else {
        Parser::PushBackToken(tok);
    }
    
    return true;
}

