/*
 * lex.cpp
 * Lexical Analyzer for the simple Ada-Like (SADAL) Language
 * CS280 - Spring 2025
 */

#include <cctype>
#include <map>

using std::map;
using namespace std;

#include "lex.h"
//Keywords or reserved words mapping
LexItem id_or_kw(const string& lexeme , int linenum)
{
	string strlexeme = lexeme;
	map<string,Token> kwmap = {
		{ "put", PUT}, { "putline", PUTLN}, { "get", GET},
		{ "if", IF }, { "elsif", ELSIF }, 
		{ "else", ELSE },
		{ "string", STRING },
		{ "integer", INT },
		{ "float", FLOAT },
		{ "character", CHAR },
		{ "boolean", BOOL },
		{ "procedure", PROCEDURE }, { "begin", BEGIN },
		{ "true", TRUE }, { "then", THEN }, { "constant", CONST },
		{ "false", FALSE }, { "is", IS }, { "end", END },
		{ "mod", MOD }, { "and", AND }, { "or", OR }, { "not", NOT },
		
	};
	Token tt ;
	
	for(int i = 0; i < lexeme.length(); i++)
	{
		strlexeme[i] = tolower(strlexeme[i]);
	}
	
	tt = IDENT;
	auto kIt = kwmap.find(strlexeme);
	if( kIt != kwmap.end() )
	{
		tt = kIt->second;
	}
	
	if(tt == TRUE || tt == FALSE)	
		tt = BCONST;
	return LexItem(tt, lexeme, linenum);
}

map<Token,string> tokenPrint = {
		{PROCEDURE, "PROCEDURE" },
		{PUT, "PUT"}, {PUTLN, "PUTLN"}, {GET, "GET"},
		{ IF, "IF" },
		{ ELSE, "ELSE" },	{ ELSIF, "ELSIF" },
		{ IDENT, "IDENT" },
		{ BOOL, "BOOL" },
		{ STRING, "STRING" },
		{ INT, "INT" },
		{ FLOAT, "FLOAT" },
		{ CHAR, "CHAR" }, { END, "END" }, { IS, "IS" },
		{ BEGIN, "BEGIN" }, { THEN, "THEN" }, { CONST, "CONST" },
		{ TRUE, "TRUE" },
		{ FALSE, "FALSE" },
		
		{ ICONST, "ICONST" },
		{ FCONST, "FCONST" },
		{ SCONST, "SCONST" },
		{ BCONST, "BCONST"},
		{ CCONST, "CCONST" }, 
					
		{ PLUS, "PLUS" },
		{ MINUS, "MINUS" },
		{ MULT, "MULT" },
		{ DIV, "DIV" },
		{ ASSOP, "ASSOP" },
		{ EQ, "EQ" },
		{ NEQ, "NEQ" },
		{ GTHAN, "GTHAN" },
		{ LTHAN, "LTHAN" },	{ GTE, "GTE" },
		{ LTE, "LTE" },	
		{ AND, "AND" },
		{ OR, "OR" },
		{ NOT, "NOT" },
		{ MOD, "MOD" }, { CONCAT, "CONCAT" },
		{ EXP, "EXP" }, 
		
		{ COMMA, "COMMA" }, { COLON, "COLON" },
		{ SEMICOL, "SEMICOL" },
		{ LPAREN, "LPAREN" },
		{ RPAREN, "RPAREN" },
		{ DOT, "DOT" },
		
		{ ERR, "ERR" },
		{ DONE, "DONE" },
};

ostream& operator<<(ostream& out, const LexItem& tok) {
	
	Token tt = tok.GetToken();
	out << tokenPrint[ tt ];
	if( tt == ICONST || tt == FCONST || tt == BCONST) {
		out << ": (" << tok.GetLexeme() << ")";
	}
	else if(tt == IDENT ){
		out << ": <" << tok.GetLexeme() << ">";
	}
	else if(tt == SCONST){
		out << ": \"" << tok.GetLexeme() << "\"";
	}
	else if(tt == CCONST){
		out << ": \'" << tok.GetLexeme() << "\'";
	}
	else if( tok == ERR ) {
		cout << ": In line " << tok.GetLinenum()+1 << ", Error Message {" << tok.GetLexeme() << "}" << endl;
	}
	cout << endl;
	return out;
}

LexItem getNextToken(istream& in, int& linenum)
{
	enum TokState { START, INID, INSTR, ININT, INREAL, INEXP, INCHAR, INCOMMENT } lexstate = START;
	string lexeme, ErrMsg;
	char ch, nextchar, nextch;
	Token tt;
	bool dec = false, intexp = false, floatexp = false;
	       
	
    while(in.get(ch)) {
    	
		switch( lexstate ) {
		case START:
			if( ch == '\n' )
			{
				linenum++;
				
			}	
                
			if( isspace(ch) )
				continue;

			

			if( isalpha(ch) ) {
				ch = tolower(ch);
				lexeme = ch;
				lexstate = INID;
				
			}
			else if( ch == '\'' ) {
				lexeme = "";
				
				lexstate = INCHAR;
				
			}
			else if(ch == '\"'){
				lexeme = "";
				lexstate = INSTR;
			}
			
			else if( isdigit(ch) ) {
				lexeme = ch;
				lexstate = ININT;
			}
			
			else if( ch == '-' )
			{
				nextchar = in.peek();
				
				if(nextchar == '-')
				{
					in.get(ch);
					
					lexstate = INCOMMENT;
					
					continue;
					
				}
				else
				{
					tt = MINUS;
					lexeme = ch;
					return LexItem(tt, lexeme, linenum);
					
				}	
			}
									
			else
			{
				tt = ERR;
				lexeme = ch;
				switch( ch ) {
				case '+':
					tt = PLUS;
					break;  
								
				case '*':
					tt = MULT;
					nextchar = in.peek();
					if(nextchar == '*' ){
						in.get(ch);
						lexeme += ch;
						tt = EXP;
					}
					break;
												
				case '=':
					tt = EQ;
					break;
				case '(':
					tt = LPAREN;
					break;			
				case ')':
					tt = RPAREN;
					break;		
				case ',':
					tt = COMMA;
					break;
				case ';':
					tt = SEMICOL;
					break;	
				case '>':
					tt = GTHAN;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = GTE;
					}
					break;
				
				case '<':
					tt = LTHAN;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = LTE;
					}
					break;
				case '&':
					tt = CONCAT;
					break;	
				case ':':
					tt = COLON;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = ASSOP;
					}
					break;
				case '/':
					tt = DIV;
					nextchar = in.peek();
					if(nextchar == '=' ){
						in.get(ch);
						lexeme += ch;
						tt = NEQ;
					}
					break;
				case '.':
					tt = DOT;				
					break;
				
				}//end of inner switch
				return LexItem(tt, lexeme, linenum);
			}//end of else
			
			break;	//break out of START case

		case INID:
			ch = tolower(ch);
			nextchar = in.peek();
			if( isalpha(ch) || isdigit(ch) || (ch == '_' ) ) {
							
				lexeme += ch;
				
				if(ch == '_' && nextchar == '_')
				{
					return id_or_kw(lexeme, linenum);
				}
			}
			else {
				in.putback(ch);
				
				return id_or_kw(lexeme, linenum);
				
			}
			break;
					
		case INCHAR:
            
			if( ch == '\n' ) {
				ErrMsg = "New line is an invalid character constant.";
				return LexItem(ERR, ErrMsg, linenum);
			}
			else if( ch == '\'' && lexeme.length() == 1) {
				
				return LexItem(CCONST, lexeme, linenum);
			}
			else if(lexeme.length() >= 1)
			{
				lexeme += ch;
				return LexItem(ERR, " Invalid character constant \'" + lexeme + "\'", linenum);
			}
			else if(ch == '\'' && lexeme.length() == 0)
			{
				return LexItem(ERR, " Invalid character constant \'\'", linenum);
			}
			lexeme += ch;
			break;
			
		case INSTR:
                         
			if( ch == '\n' ) {
				return LexItem(ERR, " Invalid string constant \"" + lexeme, linenum);
			}
			if( ch == '\"' ) {
				return LexItem(SCONST, lexeme, linenum);
			}
			lexeme += ch;
			break;
			
		case ININT:
			if( isdigit(ch) ) {
				lexeme += ch;
			}
			else if(ch == '.') {
				nextch = in.peek();
				if(isdigit(nextch))
				{
					
					in.putback(ch);
					lexstate = INREAL;
				}
				else
				{
					in.putback(ch);
					return LexItem(ICONST, lexeme, linenum);
				}
				
			}
			else if(ch == 'E' || ch == 'e' )
			{
				nextch = in.peek();
				if(nextch == '+' || nextch == '-' || isdigit(nextch))
				{
					lexeme += ch;
					in.get(ch);
					lexeme += ch;
					intexp = true;
					lexstate = INEXP;
				}
				else
				{
					in.putback(ch);
					return LexItem(ICONST, lexeme, linenum);
				}
			}
			else {
				in.putback(ch);
				return LexItem(ICONST, lexeme, linenum);
			}
			break;
		
		case INREAL:
				
			if( ch ==  '.' && isdigit(in.peek()) && !dec) {
				lexeme += ch;
				in.get(ch);
				lexeme += ch; 
				dec = true;
			}
			else if(isdigit(ch) && dec)
			{
				lexeme += ch;
			}
			else if(( ch == 'E' || ch == 'e' ) && dec ){
				nextch = in.peek();
				if(nextch == '+' || nextch == '-' || isdigit(nextch))
				{
					lexeme += ch;
					in.get(ch);
					lexeme += ch;
					floatexp = true;
					lexstate = INEXP;
				}
				else
				{
					in.putback(ch);
					return LexItem(FCONST, lexeme, linenum);
				}
			}
			
			else if((ch == '.') && dec && isdigit(in.peek())){
				lexeme += ch;
				
				return LexItem(ERR, lexeme, linenum);
			}
			else {
				in.putback(ch);
				
				return LexItem(FCONST, lexeme, linenum);
			}
			
			break;
		
		case INEXP:
			if( isdigit(ch) && (intexp || floatexp)) {
				lexeme += ch;
			}
			else 
			{
				in.putback(ch);
				if(intexp)
				{
					return LexItem(ICONST, lexeme, linenum);
				}
				if(floatexp)
				{
					return LexItem(FCONST, lexeme, linenum);
				}
			}
								
		case INCOMMENT:
			if( ch == '\n' ) {
               	lexstate = START;
               	linenum++;
				//in.putback(ch);
			}
			break;
		
		}//end of switch
	}//end of while loop
	
	if( in.eof() )
		return LexItem(DONE, "", linenum);
		
	return LexItem(ERR, "Error: Some strange symbol", linenum);
}





