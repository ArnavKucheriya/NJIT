#include <iostream>
#include <map>
#include <queue>
#include <string>
#include "lex.h"
#include "val.h"
#include "parserInterp.h"

using namespace std;

string ProgName; // Procedure Name to match at end

map<string, bool> defVar;             // Variable defined or not
map<string, Token> SymTable;           // Symbol table for type info
map<string, Value> TempsResults;       // Value storage (variables, temporaries)
vector<string> *Ids_List;              // Temporary list of IDs

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

    static void PushBackToken(LexItem& t) {
        if (pushed_back) abort();
        pushed_back = true;
        pushed_token = t;
    }
}

static int error_count = 0;

int ErrCount() { return error_count; }

void ParseError(int line, string msg) {
    ++error_count;
    cerr << line << ": " << msg << endl;
}

//-------------------------------------
//Prog ::= PROCEDURE ProcName IS ProcBody
bool Prog(istream& in, int& line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);
		
	if (tok.GetToken() == PROCEDURE) {
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == IDENT) {
			string identstr = tok.GetLexeme();
			ProgName = identstr; 
			
			if (!(defVar.find(identstr)->second))
			{
				defVar[identstr] = true;
				
				
			}
			tok = Parser::GetNextToken(in, line);
			if (tok.GetToken() == IS) {
				f1 = ProcBody(in, line); 
			
				if(f1) {
					tok = Parser::GetNextToken(in, line);
							
					if(tok.GetToken() == DONE)
					{
						
						if( defVar.size() > 0 ) {
						cout << "Declared Variables:" << endl;
						auto it = defVar.begin();
						cout << it->first ;

						for( it++; it != defVar.end(); it++ )
							cout << ", " << it->first ;
							
						}
						cout << endl <<endl;
						cout << "(DONE)" << endl;
						return true;
					}  
					else
					{
						ParseError(line, "Incorrect compilation file.");
						return false;
					}
					
				}
				else
				{
					ParseError(line, "Incorrect Procedure Definition.");
					return false;
				}
			}
			else
			{
				ParseError(line, "Incorrect Procedure Header Format.");
				return false;
			}
		}
		else
		{
			ParseError(line, "Missing Procedure Name.");
			return false;
		}
	}
	ParseError(line, "Incorrect compilation file.");
	return false;
}//End of Prog

//ProcBody ::= DeclPart BEGIN StmtList END ProcName ;
bool ProcBody(istream& in, int& line)
{
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == BEGIN)
    {
        bool f2 = StmtList(in, line);
        if (!f2)
        {
            ParseError(line, "Incorrect Procedure Body.");
            return false;
        }
    }
    else if (tok == IDENT)
    {
        Parser::PushBackToken(tok);
        bool status = DeclPart(in, line);
        if (!status)
        {
            return false; // No more errors, just stop
        }

        tok = Parser::GetNextToken(in, line);
        if (tok != BEGIN)
        {
            ParseError(line, "Missing BEGIN after Declarations.");
            return false;
        }

        bool f2 = StmtList(in, line);
        if (!f2)
        {
            ParseError(line, "Incorrect Procedure Body.");
            return false;
        }
    }
    else
    {
        ParseError(line, "Missing BEGIN after Declarations.");
        return false;
    }

    // --- After StmtList, parse END ProcName;
    tok = Parser::GetNextToken(in, line);
    if (tok.GetToken() == END)
    {
        int endLine = line;
        tok = Parser::GetNextToken(in, line);
        if (tok.GetToken() == IDENT)
        {
            if (tok.GetLexeme() != ProgName)
            {
                ParseError(endLine + 1, "Procedure name mismatch in closing end identifier.");
                return false;
            }

            tok = Parser::GetNextToken(in, line);
            if (tok.GetToken() == SEMICOL)
            {
                return true;
            }
            else
            {
                ParseError(line, "Missing end of procedure semicolon.");
                return false;
            }
        }
        else
        {
            ParseError(line, "Missing END of procedure name.");
            return false;
        }
    }
    else
    {
        ParseError(line, "Missing END of Procedure Keyword.");
        return false;
    }
}//end of ProcBody

//StmtList ::= Stmt { Stmt }
bool StmtList(istream& in, int& line)
{
	LexItem tok = Parser::GetNextToken(in, line);

    // Immediately exit if no statement and we see END/ELSIF/ELSE
    if (tok == END || tok == ELSIF || tok == ELSE) {
        Parser::PushBackToken(tok);
        return true;
    }

    Parser::PushBackToken(tok);

    bool status = Stmt(in, line);
    if (!status) {
        ParseError(line, "Syntactic error in statement list.");
        return false;
    }

    tok = Parser::GetNextToken(in, line);
    while (tok != END && tok != ELSIF && tok != ELSE)
    {
        Parser::PushBackToken(tok);
        status = Stmt(in, line);
        if (!status) {
            ParseError(line, "Syntactic error in statement list.");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
    }

    Parser::PushBackToken(tok);
    return true;
}//End of StmtList

//DeclPart ::= DeclStmt { DeclStmt }
bool DeclPart(istream& in, int& line) {
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == BEGIN)
    {
        Parser::PushBackToken(tok);
        return true;
    }
    else if (tok == IDENT)
    {
        Parser::PushBackToken(tok);
        
        // ONLY HERE, not inside DeclStmt
        Ids_List = new vector<string>;

        bool status = DeclStmt(in, line);
        if (!status)
        {
            ParseError(line, "Incorrect Declaration Statement.");
            delete Ids_List;
            return false;
        }

        delete Ids_List;
        return DeclPart(in, line);
    }
    else
    {
        ParseError(line, "Missing BEGIN after Declarations.");
        return false;
    }
}
//end of DeclPart function

//DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
bool DeclStmt(istream& in, int& line)
{
	LexItem t;
	bool status = IdentList(in, line);
	bool flag;
	
	
	if (!status)
	{
		ParseError(line, "Incorrect identifiers list in Declaration Statement.");
		return status;
	}
	
	t = Parser::GetNextToken(in, line);
	
	if(t == COLON)
	{
		t = Parser::GetNextToken(in, line);
		if(t == CONST)
		{
			t = Parser::GetNextToken(in, line);
		}
		
		if(t == INT || t == FLOAT || t == STRING || t == BOOL || t == CHAR)
		{
			t = Parser::GetNextToken(in, line);
			if(t == LPAREN)
			{
				Value val1, val2;
status = Range(in, line, val1, val2);
				if(!status)
				{
					ParseError(line, "Incorrect definition of a range in declaration statement");
					return false;
				}
				t = Parser::GetNextToken(in, line);
				if(t != RPAREN)
				{
					ParseError(line, "Incorrect syntax for a range in declaration statement");
					return false;
				}
				t = Parser::GetNextToken(in, line);
			}
			if(t == ASSOP)  
			{
				Value exprVal;
                flag = Expr(in, line, exprVal);
				
				if(!flag)
				{
					ParseError(line, "Incorrect initialization expression.");
					return false;
				}
			}
			else
			{
				Parser::PushBackToken(t);
			}
			
			t = Parser::GetNextToken(in, line);
			if(t == SEMICOL)
			{
				return true;
			}
			else
			{
				line--;
				ParseError(line, "Missing semicolon at end of statement");
				return false;
			}
		}
		else
		{
			ParseError(line, "Incorrect Declaration Type.");
			return false;
		}
	}
	else
	{
		Parser::PushBackToken(t);
		ParseError(line, "Incorrect Declaration Statement Syntax.");
		return false;
	}
	
}//End of DeclStmt

//IdList:= IDENT {,IDENT}
bool IdentList(istream& in, int& line) {
	bool status;
	string identstr;
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if(tok == IDENT)
	{
		identstr = tok.GetLexeme();
		if (!(defVar.find(identstr)->second))
		{
			defVar[identstr] = true;
			Ids_List->push_back(identstr);
			
		}	
		else
		{
			ParseError(line, "Variable Redefinition");
			return false;
		}
		
	}
	else
	{
		Parser::PushBackToken(tok);
		
		return true;
	}
	
	tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		status = IdentList(in, line);	
	}
	
	else if(tok == COLON)
	{
		Parser::PushBackToken(tok);
		return true;
	}
	else if(tok == IDENT)
	{
		ParseError(line, "Missing comma in declaration statement.");
		return false;
	}
	else {
		ParseError(line, "Invalid name for an Identifier:");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	return status;
}//End of IdentList
	

//Stmt ::= AssignStmt | PrintStmts | GetStmt | IfStmt
bool Stmt(istream& in, int& line) {
	bool status = false;
	
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {
	case IDENT:
		Parser::PushBackToken(t);
		status = AssignStmt(in, line);
		
		if(!status)
		{
			ParseError(line, "Invalid assignment statement.");
			return false;
		}
		break;
		
	case IF: 
		Parser::PushBackToken(t);
		status = IfStmt(in, line);
		if(!status)
		{
			ParseError(line, "Invalid If statement.");
			return false;
		}
		
		break;
		
	case PUT: case PUTLN:
		Parser::PushBackToken(t);
		status = PrintStmts(in, line);
		if(!status)
		{
			ParseError(line, "Invalid put statement.");
			return false;
		}
		break;
		
	case GET:
		Parser::PushBackToken(t);
		status = GetStmt(in, line);
		if(!status)
		{
			ParseError(line, "Invalid get statement.");
			return false;
		}
		break;
		
	default:
		Parser::PushBackToken(t);
		return false;
	}

	return status;
}//End of Stmt
	
//PrintStmts ::= (PutLine | Put) ( Expr) ; 
bool PrintStmts(istream& in, int& line) {
	LexItem t;
	
	t = Parser::GetNextToken(in, line);
	
	if( t != PUT && t != PUTLN)
	{
		ParseError(line, "Missing Put or PutLine Keyword");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	Value exprVal;
bool ex = Expr(in, line, exprVal);
	
	if( !ex ) {
		ParseError(line, "Missing expression for an output statement");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != SEMICOL)
	{
		line--;
		ParseError(line, "Missing semicolon at end of statement");
		return false;
	}
	return true;
}//End of PrintStmts


//IfStmt ::= IF Expr THEN StmtList { ELSIF Expr THEN StmtList }  [ ELSE StmtList ] END IF ; 
bool IfStmt(istream& in, int& line) {
	bool ex=false, status ; 
	LexItem t;
	
	t = Parser::GetNextToken(in, line);
	
	if( t != IF)
	{
		ParseError(line, "Missing IF Keyword");
		return false;
	}
	Value condVal;
ex = Expr(in, line, condVal);
	if( !ex ) {
		ParseError(line, "Missing if statement condition");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != THEN)
	{
		ParseError(line, "If-Stmt Syntax Error");
		return false;
	}
	status = StmtList(in, line);
	if(!status)
	{
		ParseError(line, "Missing Statement for If-Stmt Then-clause");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	while( t == ELSIF ) {
		Value condVal;
ex = Expr(in, line, condVal);
		if( !ex ) {
			ParseError(line, "Missing Elsif statement condition");
			return false;
		}
	
		t = Parser::GetNextToken(in, line);
		if(t != THEN)
		{
			ParseError(line, "Elsif-Stmt Syntax Error");
			return false;
		}
		status = StmtList(in, line);
		if(!status)
		{
			ParseError(line, "Missing Statement for If-Stmt Else-If-clause");
			return false;
		}
		
		t = Parser::GetNextToken(in, line);
	}
	
	if( t == ELSE ) {
		status = StmtList(in, line);
		if(!status)
		{
			ParseError(line, "Missing Statement for If-Stmt Else-clause");
			return false;
		}
		t = Parser::GetNextToken(in, line);
	}
		
	if(t == END)
	{
		t = Parser::GetNextToken(in, line);
		if(t == IF)
		{
			t = Parser::GetNextToken(in, line);
			if(t != SEMICOL)
			{
				line--;
				ParseError(line, "Missing semicolon at end of statement");
				return false;
			}	
			return true;
		}
	}
		
	ParseError(line, "Missing closing END IF for If-statement.");
	return false;
}//End of IfStmt function

//GetStmt := Get (Var) ;
bool GetStmt(istream& in, int& line)
{
	LexItem t;
	
	t = Parser::GetNextToken(in, line);
	
	if( t != GET )
	{
		ParseError(line, "Missing Get Keyword");
		return false;
	}
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	LexItem idTok;
bool ex = Var(in, line, idTok);
	
	if( !ex ) {
		ParseError(line, "Missing a variable for an input statement");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != SEMICOL)
	{
		line--;
		ParseError(line, "Missing semicolon at end of statement");
		return false;
	}
	
	return true;
}//end of GetStmt

//Var ::= ident
bool Var(istream& in, int& line, LexItem& idtok)
{
	string identstr;
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == IDENT){
		identstr = tok.GetLexeme();
        idtok = tok;
		
		if (!(defVar.find(identstr)->second))
		{
			ParseError(line, "Undeclared Variable");
			return false;
		}	
		return true;
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	return false;
}//End of Var

//AssignStmt:= Var := Expr
bool AssignStmt(istream& in, int& line) {
	
	bool varstatus = false, status = false;
	LexItem t;
	int currentLine;
	
	LexItem idTok;
varstatus = Var(in, line, idTok);

	
	currentLine = line;
	if (varstatus){
		t = Parser::GetNextToken(in, line);
		
		if (t == ASSOP){
			Value val;
status = Expr(in, line, val);
			if(!status) {
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}
            TempsResults[idTok.GetLexeme()] = val;

			
		}
		else if(t.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << t.GetLexeme() << ")" << endl;
			return false;
		}
		else {
			ParseError(line, "Missing Assignment Operator");
			return false;
		}
	}
	else {
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != SEMICOL)
	{
		if(currentLine != line)
		{
			line--;
			ParseError(line, "Missing semicolon at end of statement");
		}
		else
		{
			ParseError(line, "Illegal expression for an assignment statement");
		}
			
		return false;
	}
	return status;	
}//End of AssignStmt

//Expr ::= Relation {(AND | OR) Relation }
bool Expr(istream& in, int& line, Value& retVal)
{
    Value val1;
    if (!Relation(in, line, val1)) return false;

    LexItem tok = Parser::GetNextToken(in, line);

    while (tok == AND || tok == OR) {
        Value val2;
        if (!Relation(in, line, val2)) {
            ParseError(line, "Missing second operand after logical operator");
            return false;
        }

        if (tok == AND)
            val1 = val1 && val2;
        else
            val1 = val1 || val2;

        tok = Parser::GetNextToken(in, line);
    }

    Parser::PushBackToken(tok);
    retVal = val1;
    return true;
}//End of Expr

//Relation ::= SimpleExpr [  ( = | /= | < | <= | > | >= )  SimpleExpr ]
bool Relation(istream& in, int& line, Value& retVal)
{
    Value val1;
    if (!SimpleExpr(in, line, val1)) return false;

    LexItem tok = Parser::GetNextToken(in, line);
    if (tok == EQ || tok == NEQ || tok == LTHAN || tok == GTHAN || tok == LTE || tok == GTE) {
        Value val2;
        if (!SimpleExpr(in, line, val2)) {
            ParseError(line, "Missing second operand after relational operator");
            return false;
        }

        if (tok == EQ)
            retVal = (val1 == val2);
        else if (tok == NEQ)
            retVal = (val1 != val2);
        else if (tok == LTHAN)
            retVal = (val1 < val2);
        else if (tok == GTHAN)
            retVal = (val1 > val2);
        else if (tok == LTE)
            retVal = (val1 <= val2);
        else if (tok == GTE)
            retVal = (val1 >= val2);

        return true;
    }

    Parser::PushBackToken(tok);
    retVal = val1;
    return true;
}//End of Relation

//SimpleExpr ::= STerm {  ( + | - | & ) STerm }
bool SimpleExpr(istream& in, int& line, Value& retVal)
{
    Value val1;
    if (!STerm(in, line, val1)) return false;

    LexItem tok = Parser::GetNextToken(in, line);

    while (tok == PLUS || tok == MINUS || tok == CONCAT) {
        Value val2;
        if (!STerm(in, line, val2)) {
            ParseError(line, "Missing second operand after +, -, or &");
            return false;
        }

        if (tok == PLUS)
            val1 = val1 + val2;
        else if (tok == MINUS)
            val1 = val1 - val2;
        else if (tok == CONCAT)
            val1 = val1.Concat(val2);

        tok = Parser::GetNextToken(in, line);
    }

    Parser::PushBackToken(tok);
    retVal = val1;
    return true;
}//End of SimpleExpr

//STerm ::= [( - | + | NOT )] Term
bool STerm(istream& in, int& line, Value& retVal)
{
    LexItem t = Parser::GetNextToken(in, line);
    int sign = 0;
    
    if (t == MINUS)
        sign = -1;
    else if (t == PLUS)
        sign = 1;
    else
        Parser::PushBackToken(t);

    if (!Term(in, line, sign, retVal)) return false;
    return true;
}//End of STerm

//Term:= Factor {( * | / | MOD) Factor}
bool Term(istream& in, int& line, int sign, Value& retVal)
{
    if (!Factor(in, line, sign, retVal)) return false;

    LexItem tok = Parser::GetNextToken(in, line);

    while (tok == MULT || tok == DIV || tok == MOD) {
        Value rightVal;
        if (!Factor(in, line, sign, rightVal)) {
            ParseError(line, "Missing second operand after *, /, or MOD");
            return false;
        }

        if (tok == MULT)
            retVal = retVal * rightVal;
        else if (tok == DIV)
            retVal = retVal / rightVal;
        else if (tok == MOD)
            retVal = retVal % rightVal;

        tok = Parser::GetNextToken(in, line);
    }

    Parser::PushBackToken(tok);
    return true;
}//End of Term

//Factor ::= Primary [** Primary ] | NOT Primary
bool Factor(istream& in, int& line, int sign, Value& retVal)
{
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == NOT) {
        Value val;
        if (!Primary(in, line, sign, val)) {
            ParseError(line, "Incorrect operand for NOT operator");
            return false;
        }
        retVal = !val;
        return true;
    }
    else {
        Parser::PushBackToken(tok);
    }

    Value val;
    if (!Primary(in, line, sign, val)) {
        ParseError(line, "Incorrect operand");
        return false;
    }

    tok = Parser::GetNextToken(in, line);
    if (tok == EXP) {
        Value val2;
        if (!Primary(in, line, sign, val2)) {
            ParseError(line, "Missing right operand for exponentiation");
            return false;
        }
        retVal = val.Exp(val2);
        return true;
    }

    Parser::PushBackToken(tok);
    retVal = val;
    return true;
}
//End of Factor

//Primary ::= Name | ICONST | FCONST | SCONST | BCONST | CCONST | (Expr)
bool Primary(istream& in, int& line, int sign, Value& retVal)
{
    LexItem tok = Parser::GetNextToken(in, line);

    if (tok == IDENT) {
		Parser::PushBackToken(tok);
		if (!Name(in, line, sign, retVal)) {
			return false;  // Dont call ParseError here again
		}
		return true;
	}
	
    else if (tok == ICONST) {
        int val = stoi(tok.GetLexeme());
        retVal = Value(val);
    }
    else if (tok == FCONST) {
        double val = stod(tok.GetLexeme());
        retVal = Value(val);
    }
    else if (tok == SCONST) {
        retVal = Value(tok.GetLexeme());
    }
    else if (tok == CCONST) {
        retVal = Value(tok.GetLexeme()[0]);
    }
    else if (tok == BCONST) {
        bool val = (tok.GetLexeme() == "true");
        retVal = Value(val);
    }
    else if (tok == LPAREN) {
        if (!Expr(in, line, retVal)) {
            ParseError(line, "Invalid expression inside parenthesis.");
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            ParseError(line, "Missing right parenthesis.");
            return false;
        }
        return true;
    }
    else {
        ParseError(line, "Invalid Primary");
        return false;
    }

    // Apply unary sign if necessary
    if (sign == -1) {
        if (retVal.IsInt())
            retVal = Value(-retVal.GetInt());
        else if (retVal.IsReal())
            retVal = Value(-retVal.GetReal());
        else {
            ParseError(line, "Unary '-' applied to non-numeric value.");
            return false;
        }
    }

    return true;
}//End of Primary

bool Name(istream& in, int& line, int sign, Value& retVal)
{
    LexItem tok = Parser::GetNextToken(in, line);
    string varname = tok.GetLexeme();

    if (defVar.find(varname) == defVar.end()) {
        ParseError(line, "Undeclared variable " + varname);
        return false;
    }

    if (TempsResults.find(varname) == TempsResults.end()) {
        ParseError(line, "Uninitialized variable " + varname);
        return false;
    }

    retVal = TempsResults[varname];

    tok = Parser::GetNextToken(in, line);
    if (tok == LPAREN) {
        Value low, high;
        if (!Range(in, line, low, high)) {
            return false;
        }
        tok = Parser::GetNextToken(in, line);
        if (tok != RPAREN) {
            ParseError(line, "Missing right parenthesis after range.");
            return false;
        }
        // You can extend handling range if needed
    }
    else {
        Parser::PushBackToken(tok);
    }

    return true;
}//End of Name

bool Range(istream& in, int& line, Value& retVal1, Value& retVal2)
{
    if (!SimpleExpr(in, line, retVal1)) {
        ParseError(line, "Invalid lower bound expression in range.");
        return false;
    }

    LexItem tok = Parser::GetNextToken(in, line);
    if (tok != DOT) {
        ParseError(line, "Missing '.' in range.");
        return false;
    }

    tok = Parser::GetNextToken(in, line);
    if (tok != DOT) {
        ParseError(line, "Missing '..' in range.");
        return false;
    }

    if (!SimpleExpr(in, line, retVal2)) {
        ParseError(line, "Invalid upper bound expression in range.");
        return false;
    }

    return true;
}//End of Range

// --- Runtime Error Helper ---
Value RunTimeErr(const string& errmsg) {
    cerr << "RUNTIME ERROR: " << errmsg << endl;
    return Value();
}

// + Operator
Value Value::operator+(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();

    if (IsInt() && op.IsInt()) return Value(Itemp + op.Itemp);
    if (IsReal() && op.IsReal()) return Value(Rtemp + op.Rtemp);

    return RunTimeErr("Illegal Mixed Type Operands for +");
}

// - Operator
Value Value::operator-(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();

    if (IsInt() && op.IsInt()) return Value(Itemp - op.Itemp);
    if (IsReal() && op.IsReal()) return Value(Rtemp - op.Rtemp);

    return RunTimeErr("Illegal Mixed Type Operands for -");
}

// * Operator
Value Value::operator*(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();

    if (IsInt() && op.IsInt()) return Value(Itemp * op.Itemp);
    if (IsReal() && op.IsReal()) return Value(Rtemp * op.Rtemp);

    return RunTimeErr("Illegal Mixed Type Operands for *");
}

// / Operator
Value Value::operator/(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();

    if ((op.IsInt() && op.Itemp == 0) || (op.IsReal() && op.Rtemp == 0))
        return RunTimeErr("Illegal Division by Zero");

    if (IsInt() && op.IsInt()) return Value(Itemp / op.Itemp);
    if (IsReal() && op.IsReal()) return Value(Rtemp / op.Rtemp);

    return RunTimeErr("Illegal Mixed Type Operands for /");
}

// MOD Operator
Value Value::operator%(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();

    if (IsInt() && op.IsInt()) {
        if (op.Itemp == 0) return RunTimeErr("Illegal Modulus by Zero");
        return Value(Itemp % op.Itemp);
    }

    return RunTimeErr("MOD Operator requires Integer Operands");
}

// == Operator
Value Value::operator==(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();
    if (T != op.T) return RunTimeErr("Illegal Mixed Type Operands for ==");

    switch (T) {
        case VINT: return Value(Itemp == op.Itemp);
        case VREAL: return Value(Rtemp == op.Rtemp);
        case VSTRING: return Value(Stemp == op.Stemp);
        case VCHAR: return Value(Ctemp == op.Ctemp);
        case VBOOL: return Value(Btemp == op.Btemp);
        default: return Value();
    }
}

// != Operator
Value Value::operator!=(const Value& op) const {
    Value eq = (*this) == op;
    if (eq.IsErr()) return eq;
    return Value(!eq.GetBool());
}

// > Operator
Value Value::operator>(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();
    if (T != op.T) return RunTimeErr("Illegal Mixed Type Operands for >");

    switch (T) {
        case VINT: return Value(Itemp > op.Itemp);
        case VREAL: return Value(Rtemp > op.Rtemp);
        case VSTRING: return Value(Stemp > op.Stemp);
        case VCHAR: return Value(Ctemp > op.Ctemp);
        default: return Value();
    }
}

// < Operator
Value Value::operator<(const Value& op) const {
    if (IsErr() || op.IsErr()) return Value();
    if (T != op.T) return RunTimeErr("Illegal Mixed Type Operands for <");

    switch (T) {
        case VINT: return Value(Itemp < op.Itemp);
        case VREAL: return Value(Rtemp < op.Rtemp);
        case VSTRING: return Value(Stemp < op.Stemp);
        case VCHAR: return Value(Ctemp < op.Ctemp);
        default: return Value();
    }
}

// <= Operator
Value Value::operator<=(const Value& op) const {
    Value lt = (*this) < op;
    Value eq = (*this) == op;
    if (lt.IsErr() || eq.IsErr()) return Value();
    return Value(lt.GetBool() || eq.GetBool());
}

// >= Operator
Value Value::operator>=(const Value& op) const {
    Value gt = (*this) > op;
    Value eq = (*this) == op;
    if (gt.IsErr() || eq.IsErr()) return Value();
    return Value(gt.GetBool() || eq.GetBool());
}

// && Operator
Value Value::operator&&(const Value& op) const {
    if (IsBool() && op.IsBool()) return Value(Btemp && op.Btemp);
    return RunTimeErr("AND Operator requires Boolean Operands");
}

// || Operator
Value Value::operator||(const Value& op) const {
    if (IsBool() && op.IsBool()) return Value(Btemp || op.Btemp);
    return RunTimeErr("OR Operator requires Boolean Operands");
}

// ! Operator
Value Value::operator!() const {
    if (IsBool()) return Value(!Btemp);
    return RunTimeErr("NOT Operator requires Boolean Operand");
}

// Concat
Value Value::Concat(const Value& op) const {
    if ((IsString() || IsChar()) && (op.IsString() || op.IsChar())) {
        string left = (IsChar() ? string(1, Ctemp) : Stemp);
        string right = (op.IsChar() ? string(1, op.Ctemp) : op.Stemp);
        return Value(left + right);
    }
    return RunTimeErr("Concatenation requires String or Character Operands");
}

// Exp
Value Value::Exp(const Value& op) const {
    if (IsReal() && op.IsInt()) {
        if (op.Itemp == 0) return Value(1.0);
        return Value(pow(Rtemp, op.Itemp));
    }
    return RunTimeErr("Exponentiation requires Real base and Integer exponent");
}