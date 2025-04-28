/* Implementation of Recursive-Descent Parser
	for the Simple Ada-Like (SADAL) Language
 * parser.cpp
 * Programming Assignment 2
 * Spring 2025
*/
#include <queue>
#include "parser.h"


map<string, bool> defVar;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}


//Prog ::= PROCEDURE ProcName IS ProcBody
bool Prog(istream& in, int& line)
{
	bool f1;
	LexItem tok = Parser::GetNextToken(in, line);
		
	if (tok.GetToken() == PROCEDURE) {
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == IDENT) {
			string identstr = tok.GetLexeme();
			
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
	bool status = false, f2;
	LexItem tok;
	
	status = DeclPart(in, line);
	if (!status)
	{
		ParseError(line, "Incorrect Declaration Part.");
		return status;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok == BEGIN)
	{
		f2 = StmtList(in, line);
		if(!f2)
		{
			ParseError(line, "Incorrect Proedure Body.");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if (tok.GetToken() == END)
		{	
			tok = Parser::GetNextToken(in, line);
			if (tok.GetToken() == IDENT)
			{
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
	}
    ParseError(line, "Incorrect procedure body.");
	return false;
}//end of ProcBody

//StmtList ::= Stmt { Stmt }
bool StmtList(istream& in, int& line)
{
	bool status;
	LexItem tok;
	
	status = Stmt(in, line);
	tok = Parser::GetNextToken(in, line);
	while(status && (tok != END && tok != ELSIF && tok != ELSE))
	{
		Parser::PushBackToken(tok);
		status = Stmt(in, line);
		tok = Parser::GetNextToken(in, line);
	}
	if(!status)
	{
		ParseError(line, "Syntactic error in statement list.");
		return false;
	}
	Parser::PushBackToken(tok); 
	return true;
}//End of StmtList

//DeclPart ::= DeclStmt { DeclStmt }
bool DeclPart(istream& in, int& line) {
	bool status = false;
	LexItem tok;
	
	status = DeclStmt(in, line);
	if(status)
	{
		tok = Parser::GetNextToken(in, line);
		if(tok == BEGIN )
		{
			Parser::PushBackToken(tok);
			return true;
		}
		else 
		{
			Parser::PushBackToken(tok);
			status = DeclPart(in, line);
		}
	}
	else
	{
		ParseError(line, "Non-recognizable Declaration Part.");
		return false;
	}
	return true;
}//end of DeclPart function

//DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
bool DeclStmt(istream& in, int& line)
{
	LexItem t;
	Id_List = new queue<string>;
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
				status = Range(in, line);
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
				flag = Expr(in, line);
				
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
			Id_List->push(identstr);
			
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
	
	bool ex = Expr(in, line);
	
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
	ex = Expr(in, line);
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
		ex = Expr(in, line);
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
	
	bool ex = Var(in, line);
	
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
bool Var(istream& in, int& line)
{
	string identstr;
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == IDENT){
		identstr = tok.GetLexeme();
		
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
	
	varstatus = Var( in, line);
	
	currentLine = line;
	if (varstatus){
		t = Parser::GetNextToken(in, line);
		
		if (t == ASSOP){
			status = Expr(in, line);
			if(!status) {
				ParseError(line, "Missing Expression in Assignment Statement");
				return status;
			}
			
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
bool Expr(istream& in, int& line) {
	LexItem tok;
	bool t1 = Relation(in, line);
		
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while ( tok == OR || tok == AND) 
	{
		t1 = Relation(in, line);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Expr

//Relation ::= SimpleExpr [  ( = | /= | < | <= | > | >= )  SimpleExpr ]
bool Relation(istream& in, int& line) {
	LexItem tok;
	bool t1 = SimpleExpr(in, line);
		
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	if ( tok == EQ || tok == NEQ || tok == LTHAN || tok == GTHAN || tok == LTE || tok == GTE)
	{
		t1 = SimpleExpr(in, line);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	
	Parser::PushBackToken(tok);
	return true;
}//End of Relation

//SimpleExpr ::= STerm {  ( + | - | & ) STerm }
bool SimpleExpr(istream& in, int& line) {
	bool t1 = STerm(in, line);
	LexItem tok;
	
	if( !t1 ) {
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	while ( tok == PLUS || tok == MINUS || tok == CONCAT )
	{
		t1 = STerm(in, line);
		if( !t1 ) 
		{
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok = Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}		
	}
	Parser::PushBackToken(tok);
	return true;
}//End of SimpleExpr

//STerm ::= [( - | + | NOT )] Term
bool STerm(istream& in, int& line)
{
	LexItem t = Parser::GetNextToken(in, line);
	bool status;
	int sign = 0;
	if(t == MINUS )
	{
		sign = -1;
	}
	else if(t == PLUS)
	{
		sign = 1;
	}
	else
		Parser::PushBackToken(t);
		
	status = Term(in, line, sign);
	return status;
}//End of STerm

//Term:= Factor {( * | / | MOD) Factor}
bool Term(istream& in, int& line, int sign) {
	bool t1 = Factor(in, line, sign);
	LexItem tok;
	if( !t1 ) {
		return false;
	}
	
	tok	= Parser::GetNextToken(in, line);
	if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
	}
	while ( tok == MULT || tok == DIV  || tok == MOD)
	{
		t1 = Factor(in, line, sign);
		
		if( !t1 ) {
			ParseError(line, "Missing operand after operator");
			return false;
		}
		
		tok	= Parser::GetNextToken(in, line);
		if(tok.GetToken() == ERR){
			ParseError(line, "Unrecognized Input Pattern");
			cout << "(" << tok.GetLexeme() << ")" << endl;
			return false;
		}
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Term

//Factor ::= Primary [** Primary ] | NOT Primary
bool Factor(istream& in, int& line, int sign)
{
	LexItem tok;
	bool t1;
	
	tok = Parser::GetNextToken(in, line);
	if(tok == NOT)
	{
		t1 = Primary(in, line, sign);
		if( !t1 ) {
			ParseError(line, "Incorrect operand for NOT operator");
			return false;
		}
		return true;
	}
	else
	{
		Parser::PushBackToken(tok);
	}
	
	t1 = Primary(in, line, sign);
	
	if( !t1 ) {
		ParseError(line, "Incorrect operand");
		return false;
	}
	
	tok = Parser::GetNextToken(in, line);
	if( tok == EXP   ) 
	{
		t1 = Primary(in, line, sign);
		if( !t1 ) {
			ParseError(line, "Missing raised power for exponent operator");
			return false;
		}
		return true;
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Factor

//Primary ::= Name | ICONST | FCONST | SCONST | BCONST | CCONST | (Expr)
bool Primary(istream& in, int& line, int sign) {
	LexItem tok = Parser::GetNextToken(in, line);
	bool status;
	
	if( tok == IDENT ) {
		
		Parser::PushBackToken(tok);
		status = Name(in, line);
		if(!status)
		{
			ParseError(line, "Invalid reference to a variable.");
			return false;
		}
		else
		{
			return true;
		}
	}
	else if( tok == ICONST ) {
		
		return true;
	}
	else if( tok == SCONST ) {
		
		return true;
	}
	else if( tok == FCONST ) {
		
		return true;
	}
	else if( tok == BCONST ) {
		
		return true;
	}
	else if( tok == CCONST ) {
		
		return true;
	}
	else if( tok == LPAREN ) {
		bool ex = Expr(in, line);
		if( !ex ) {
			ParseError(line, "Invalid expression after left parenthesis");
			return false;
		}
		if( Parser::GetNextToken(in, line) == RPAREN )
			return ex;
		else 
		{
			Parser::PushBackToken(tok);
			ParseError(line, "Missing right parenthesis after expression");
			return false;
		}
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	Parser::PushBackToken(tok);
	ParseError(line, "Invalid Expression");
	return false;
}//End of Primary

bool Name(istream& in, int& line)
{
	bool status;
	LexItem tok = Parser::GetNextToken(in, line);
	string lexeme = tok.GetLexeme();
	if (!(defVar.find(lexeme)->second))
	{
		ParseError(line, "Using Undefined Variable");
		return false;	
	}
	tok = Parser::GetNextToken(in, line);
	if(tok == LPAREN)
	{
		status = Range(in, line);
		if(!status)
		{
			ParseError(line, "Invalid range definition");
			return false;
		}
		tok = Parser::GetNextToken(in, line);
		if(tok != RPAREN)
		{
			ParseError(line, "Invalid syntax for an index or range definition.");
			return false;
		}
		return true;
	}
	Parser::PushBackToken(tok);
	
	return true;
}//End of Name

bool Range(istream& in, int& line)
{
	bool status;
	LexItem tok;
	
	status = SimpleExpr(in, line);
	if(!status)
	{
		ParseError(line, "Invalid expression for an index or a lower bound definition of a range.");
		return false;
	}
	tok = Parser::GetNextToken(in, line);
	if(tok == DOT)
	{	
		tok = Parser::GetNextToken(in, line);
		if(tok == DOT)
		{
			status = SimpleExpr(in, line);
			if(!status)
			{
				ParseError(line, "Invalid expression for an upper bound definition of a range.");
				return false;
			}	
		}
		else
		{
			ParseError(line, "Invalid definition of a range.");
			return false;
		}
		
		return true;
	}
	Parser::PushBackToken(tok);
	return true;
}//End of Range
