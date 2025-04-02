/* 
 * parser.h
 * Programming Assignment 2
 * Fall 2023
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>

using namespace std;

#include "lex.h"

extern bool Prog(istream& in, int& line);
extern bool ProcBody(istream& in, int& line);
extern bool DeclPart(istream& in, int& line);
extern bool DeclStmt(istream& in, int& line);
extern bool Type(istream& in, int& line);
extern bool StmtList(istream& in, int& line);
extern bool Stmt(istream& in, int& line);
extern bool PrintStmts(istream& in, int& line);
extern bool GetStmt(istream& in, int& line);
extern bool IfStmt(istream& in, int& line);
extern bool AssignStmt(istream& in, int& line);
extern bool Var(istream& in, int& line);
extern bool Expr(istream& in, int& line);
extern bool Relation(istream& in, int& line);
extern bool SimpleExpr(istream& in, int& line);
extern bool STerm(istream& in, int& line);
extern bool Term(istream& in, int& line, int sign);
extern bool Factor(istream& in, int& line, int sign);
extern bool Primary(istream& in, int& line, int sign);
extern bool Name(istream& in, int& line);
extern bool Range(istream& in, int& line);

extern int ErrCount();

#endif /* PARSE_H_ */
