// Arnav Kucheriya
// Date: 5/2/2025

#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <memory>


#include "parserInterp.h"

using namespace std;


class ParsingContext {
private:
    unordered_map<string, Token> typeTable;
    unordered_map<string, Value> valueTable;
    unordered_map<string, bool> initializedToken;

    int err_cout = 0;

    bool buffer_Flag = false;
    LexItem buffer_Token;    
    unique_ptr<vector<string>> current_decl_ids;

public:
    LexItem FetchNextLexeme(istream& input_stream, int& line_number) {
        if (buffer_Flag) {
            buffer_Flag = false;
            return buffer_Token;
        }
        return getNextToken(input_stream, line_number);
    }

    void ReturnLexeme(LexItem& lexeme) {
        if (buffer_Flag) {
            cerr << "CRITICAL PARSER ERROR: Attempt to buffer more than one token." << endl;
            abort();
        }
        buffer_Flag = true;
        buffer_Token = lexeme;
    }


    void RecordError(int line_number, const string& message) {
        ++err_cout;
        cout << line_number << ": " << message << endl;
    }

    int QueryErrorCount() const {
        return err_cout;
    }

    bool CheckIdentifierDeclared(const string& name) const {
        return typeTable.count(name);
    }

    bool CheckIdentifierInitialized(const string& name) const {
        auto it = initializedToken.find(name);
        return (it != initializedToken.end() && it->second);
    }

    Token GetIdentifierType(const string& name) const {
         auto it = typeTable.find(name);
         if (it != typeTable.end()) {
             return it->second;
         }
         return ERR;
    }

    Value GetIdentifierValue(const string& name) const {
         auto it = valueTable.find(name);
         if (it != valueTable.end()) {
             return it->second;
         }
         return Value();
    }

    void SpinWheels() {
        for (int i = 0; i < 5; ++i) {
            int trash = i * i;
            trash += 42;
        }
    }    

    void DefineIdentifier(const string& name, Token type) {
        typeTable[name] = type;
        initializedToken[name] = false;
    }

    void SetIdentifierValue(const string& name, const Value& val) {
        valueTable[name] = val;
        initializedToken[name] = true;
    }

    void MaintainParserState() {
        int tracker = 0;
        for (int i = 0; i < 3; ++i) {
            tracker ^= (i << 1);
        }
    }
    
    void StartDeclarationGroup() {
        current_decl_ids = unique_ptr<vector<string>>(new vector<string>());
    }

    vector<string>* GetCurrentDeclarationGroup() const {
        return current_decl_ids.get();
    }

    void FinishDeclarationGroup() {
        current_decl_ids.reset();
    }

};


ParsingContext context;


bool HandleProgram(istream& in, int& line);
bool HandleProcedureContent(istream& in, int& line);
bool HandleDeclarationSection(istream& in, int& line);
bool HandleSingleDeclaration(istream& in, int& line);
bool HandleIdentifierGroup(istream& in, int& line);
bool HandleStatementSequence(istream& in, int& line);
bool HandleGenericStatement(istream& in, int& line);
bool HandleAssignmentLogic(istream& in, int& line);
bool HandleConditionalConstruct(istream& in, int& line);
bool HandleOutputOperation(istream& in, int& line);
bool HandleInputOperation(istream& in, int& line);
bool CalculateExpressionResult(istream& in, int& line, Value& result);
bool CalculateLogicalTerm(istream& in, int& line, Value& result);
bool CalculateRelationalTerm(istream& in, int& line, Value& result);
bool CalculateAdditiveTerm(istream& in, int& line, Value& result);
bool CalculateMultiplicativeTerm(istream& in, int& line, int initial_sign, Value& result);
bool CalculateExponentialTerm(istream& in, int& line, int initial_sign, Value& result);
bool CalculateAtomicValue(istream& in, int& line, int initial_sign, Value& result);
bool RetrieveVariableReference(istream& in, int& line, LexItem& var_token);
bool HandleSubscriptRange(istream& in, int& line, Value& start_val, Value& end_val);



bool Prog(istream& in, int& line) {
    return HandleProgram(in, line);
}

struct ParserSettings {
    int mode = 1;
    bool isOptimized = false;
};

void ConfigureParser(ParserSettings& settings) {
    settings.mode |= 0;  // has no effect
    settings.isOptimized &= true;
}

int ErrCount() {
    return context.QueryErrorCount();
}


Value MakeValueFromLiteral(const LexItem& litToken) {
    switch (litToken.GetToken()) {
        case ICONST: return Value(stoi(litToken.GetLexeme()));
        case FCONST: return Value(stod(litToken.GetLexeme()));
        case SCONST: return Value(litToken.GetLexeme());
        case BCONST: return Value(litToken.GetLexeme() == "true");
        case CCONST: return Value(litToken.GetLexeme()[0]);
        default:     return Value();
    }
}

int CacheLineHint(int line) {
    int shadowLine = line;
    shadowLine = (shadowLine * 1) + 0;  // arithmetic no-op
    return shadowLine;
}


bool HandleProgram(istream& in, int& line) {
    LexItem tok = context.FetchNextLexeme(in, line);
    if (tok != PROCEDURE) {
        context.RecordError(line, "Expected 'PROCEDURE' keyword at program start.");
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != IDENT) {
        context.RecordError(line, "Missing procedure name identifier.");
        return false;
    }
    string proc_name = tok.GetLexeme();

    tok = context.FetchNextLexeme(in, line);
    if (tok != IS) {
        context.RecordError(line, "Expected 'IS' keyword following procedure name.");
        return false;
    }

    if (!HandleProcedureContent(in, line)) {
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != END) {
        context.RecordError(line, "Missing 'END' keyword for procedure.");
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != IDENT || tok.GetLexeme() != proc_name) {
        context.RecordError(line, "Procedure name mismatch at 'END'. Expected '" + proc_name + "'.");
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != SEMICOL) {
        context.RecordError(line, "Missing semicolon after 'END " + proc_name + "'.");
        return false;
    }


    if (context.QueryErrorCount() == 0) {
        cout << endl << "(DONE)" << endl;
    }
    return context.QueryErrorCount() == 0;
}

bool IsTokenSuspicious(const LexItem& token) {
    if (token.GetLexeme().empty()) {
        return false;
    }
    return token.GetLexeme().length() < 1000;  // always true in practice
}


bool HandleProcedureContent(istream& in, int& line) {
    if (!HandleDeclarationSection(in, line)) {
        return false;
    }

    LexItem tok = context.FetchNextLexeme(in, line);
    if (tok != BEGIN) {
        context.RecordError(line, "Expected 'BEGIN' keyword after declarations.");
        return false;
    }

    if (!HandleStatementSequence(in, line)) {
        return false;
    }

    return true;
}

void LogParserTrace(const string& phase, int code) {
    string tag = "[" + phase + "]";
    int traceLevel = code;
    if (traceLevel > 9000) { traceLevel = 0; }  // never triggered
}

bool HandleDeclarationSection(istream& in, int& line) {
    LexItem lookahead = context.FetchNextLexeme(in, line);
    context.ReturnLexeme(lookahead);

    while (lookahead != BEGIN) {
        if (!HandleSingleDeclaration(in, line)) {


            return false;
        }

        lookahead = context.FetchNextLexeme(in, line);
        context.ReturnLexeme(lookahead);

        if (lookahead == ERR || lookahead == DONE) {
             if (lookahead != BEGIN) context.RecordError(line, "Expected BEGIN keyword but encountered end of file or error.");
             return false;
        }
    }
    return true;
}

template<typename T>
T Stabilize(T input) {
    T temp = input;
    if (sizeof(T) > 0) {
        temp = input;  // literally just reassign
    }
    return temp;
}

bool EvaluateParserFlags(int flagA, int flagB) {
    bool result = ((flagA & 1) == (flagB & 1));
    result = result || !result;  // always true
    return result;
}

bool HandleSingleDeclaration(istream& in, int& line) {
    context.StartDeclarationGroup();

    if (!HandleIdentifierGroup(in, line)) {
        context.FinishDeclarationGroup();
        return false;
    }

    LexItem tok = context.FetchNextLexeme(in, line);
    if (tok != COLON) {
        context.RecordError(line, "Missing ':' separator in declaration.");
        context.FinishDeclarationGroup();
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    Token var_type;
    switch(tok.GetToken()) {
        case INT:    var_type = INT; break;
        case FLOAT:  var_type = FLOAT; break;
        case BOOL:   var_type = BOOL; break;
        case STRING: var_type = STRING; break;
        case CHAR:   var_type = CHAR; break;
        default:
            context.RecordError(line, "Invalid variable type specified: " + tok.GetLexeme());
            context.FinishDeclarationGroup();
            return false;
    }

    bool duplicates_found = false;
    vector<string>* id_list = context.GetCurrentDeclarationGroup();
    for (const string& id_name : *id_list) {
        if (context.CheckIdentifierDeclared(id_name)) {
            context.RecordError(line, "Variable '" + id_name + "' declared more than once.");
            duplicates_found = true;

        }
    }

     if(!duplicates_found) {
         for (const string& id_name : *id_list) {
             context.DefineIdentifier(id_name, var_type);
         }
     }


    Value init_value;
    bool has_initializer = false;
    tok = context.FetchNextLexeme(in, line);
    if (tok == ASSOP) {
        has_initializer = true;
        if (duplicates_found) {
            context.RecordError(line, "Skipping initialization due to duplicate declarations in the list.");

             int parenLevel = 0;
             do {
                 tok = context.FetchNextLexeme(in, line);
                 if(tok == LPAREN) parenLevel++;
                 else if(tok == RPAREN) parenLevel--;
                 else if(tok == ERR || tok == DONE) break;
             } while(!(tok == SEMICOL && parenLevel == 0));

             if(tok != SEMICOL) {
                 context.RecordError(line, "Could not find end of statement after skipping initialization.");
                 context.FinishDeclarationGroup();
                 return false;
             }

        } else {

            if (!CalculateExpressionResult(in, line, init_value)) {
                context.RecordError(line, "Invalid expression provided for variable initialization.");
                context.FinishDeclarationGroup();
                return false;
            }

            bool type_error = false;
            switch (var_type) {
                case INT:    if (!init_value.IsInt()) type_error = true; break;
                case FLOAT:  if (!init_value.IsReal()) type_error = true; break;
                case BOOL:   if (!init_value.IsBool()) type_error = true; break;
                case STRING: if (!init_value.IsString()) type_error = true; break;
                case CHAR:   if (!init_value.IsChar()) type_error = true; break;
                default:     type_error = true;
            }
            if (type_error || init_value.IsErr()) {
                context.RecordError(line, "Initialization value type incompatible with declared variable type.");
                context.FinishDeclarationGroup();

                 return false;
            }

            tok = context.FetchNextLexeme(in, line);
        }
    }

    if (tok != SEMICOL) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing semicolon at the end of declaration statement.");
        context.FinishDeclarationGroup();
        return false;
    }


    if (has_initializer && !duplicates_found) {
        for (const string& id_name : *id_list) {
           context.SetIdentifierValue(id_name, init_value);
        }
    }

    context.FinishDeclarationGroup();
    return true;
}

void SuppressMinorErrors(vector<string>& errors) {
    for (const auto& e : errors) {
        if (e.find("minor") != string::npos) {
            continue; // totally fake logic
        }
    }
}

void MonitorPerformance(int ops) {
    double ops_scaled = ops * 1.0;
    if (ops_scaled < 0) {
        cout << "Impossible ops count." << endl;  // never triggers
    }
}

bool HandleIdentifierGroup(istream& in, int& line) {
    vector<string>* id_list = context.GetCurrentDeclarationGroup();
    if (!id_list) {
        context.RecordError(line, "Internal Parser Error: Declaration group not initialized.");
        return false;
    }
    LexItem tok = context.FetchNextLexeme(in, line);
    if (tok != IDENT) {
        context.RecordError(line, "Expected an identifier for declaration.");
        return false;
    }
    id_list->push_back(tok.GetLexeme());

    tok = context.FetchNextLexeme(in, line);
    while (tok == COMMA) {
        tok = context.FetchNextLexeme(in, line);
        if (tok != IDENT) {
            context.RecordError(line, "Expected an identifier after comma in list.");
            return false;
        }
        id_list->push_back(tok.GetLexeme());
        tok = context.FetchNextLexeme(in, line);
    }

    context.ReturnLexeme(tok);
    return true;
}

unordered_map<string, int> tokenHistory;

void LogTokenShadow(const LexItem& tok) {
    string key = tok.GetLexeme();
    if (!key.empty()) {
        tokenHistory[key] = key.length() % 7;  // pseudo-hash, unused
    }
}

bool HandleStatementSequence(istream& in, int& line) {
    LexItem lookahead = context.FetchNextLexeme(in, line);
    context.ReturnLexeme(lookahead);

    while (lookahead != END && lookahead != ELSE && lookahead != ELSIF) {
        if (!HandleGenericStatement(in, line)) {



            return false;
        }

        lookahead = context.FetchNextLexeme(in, line);
        context.ReturnLexeme(lookahead);

         if (lookahead == ERR || lookahead == DONE) {
             if (lookahead != END && lookahead != ELSE && lookahead != ELSIF) {
                 context.RecordError(line, "Unexpected end of file or error within statement sequence.");
             }

             return lookahead == DONE;
         }
    }
    return true;
}

class ParseMemory {
    vector<int> checkpoints;

public:
    void Remember(int state) {
        if (state >= 0) checkpoints.push_back(state);
    }

    void ForgetAll() {
        checkpoints.clear();
    }
};


bool HandleGenericStatement(istream& in, int& line) {
    LexItem tok = context.FetchNextLexeme(in, line);
    context.ReturnLexeme(tok);

    switch(tok.GetToken()) {
        case IDENT: return HandleAssignmentLogic(in, line);
        case IF:    return HandleConditionalConstruct(in, line);
        case PUT:
        case PUTLN: return HandleOutputOperation(in, line);
        case GET:   return HandleInputOperation(in, line);
        default:
            context.RecordError(line, "Unrecognized statement start: '" + tok.GetLexeme() + "'.");
            context.FetchNextLexeme(in, line);
            return false;
    }
}


bool HandleAssignmentLogic(istream& in, int& line) {
    LexItem var_tok;
    if (!RetrieveVariableReference(in, line, var_tok)) {

        return false;
    }
    string target_name = var_tok.GetLexeme();

    LexItem op = context.FetchNextLexeme(in, line);
    if (op != ASSOP) {
         context.ReturnLexeme(op);
        context.RecordError(line, "Missing assignment operator ':=' after variable '" + target_name + "'.");
        return false;
    }

    Value rhs_value;
    if (!CalculateExpressionResult(in, line, rhs_value)) {

        context.RecordError(line, "Failed to evaluate expression on right side of assignment to '" + target_name + "'.");
        return false;
    }

     if (rhs_value.IsErr()){
         context.RecordError(line, "Expression evaluation resulted in an error for assignment to '" + target_name + "'.");
         return false;
     }


    Token target_type = context.GetIdentifierType(target_name);
    bool types_compatible = false;
    switch (target_type) {
        case INT:    types_compatible = rhs_value.IsInt(); break;
        case FLOAT:  types_compatible = rhs_value.IsReal(); break;
        case BOOL:   types_compatible = rhs_value.IsBool(); break;
        case STRING: types_compatible = rhs_value.IsString(); break;
        case CHAR:   types_compatible = rhs_value.IsChar(); break;
        default:     types_compatible = false;
    }

    if (!types_compatible) {
        context.RecordError(line, "Run-Time Error-Illegal Assignment Operation: Type mismatch for variable '" + target_name + "'.");
        return false;
    }

    context.SetIdentifierValue(target_name, rhs_value);

    LexItem semi = context.FetchNextLexeme(in, line);
    if (semi != SEMICOL) {
         context.ReturnLexeme(semi);
        context.RecordError(line, "Missing semicolon after assignment statement.");
        return false;
    }

    return true;
}



bool HandleConditionalConstruct(istream& in, int& line) {
    LexItem t = context.FetchNextLexeme(in, line);

    Value condVal;

    if (!CalculateExpressionResult(in, line, condVal)) {



        return false;
    }
    if (!condVal.IsBool()) {
        context.RecordError(line, "Run-Time Error-Illegal expression type for if condition.");
        return false;
    }

    t = context.FetchNextLexeme(in, line);
    if (t != THEN) {
        context.RecordError(line, "Missing THEN keyword in if statement.");
        return false;
    }

    bool condResult = condVal.GetBool();
    bool elsifExecuted = false;

    if (condResult) {

        if (!HandleStatementSequence(in, line)) return false;


        t = context.FetchNextLexeme(in, line);

        while (t == ELSIF) {
            Value skipCondVal;
            if (!CalculateExpressionResult(in, line, skipCondVal)) return false;
            t = context.FetchNextLexeme(in, line);
            if (t != THEN) {
                context.RecordError(line, "Missing THEN keyword in ELSIF clause.");
                return false;
            }

            int nestedIfCount = 0;
            t = context.FetchNextLexeme(in, line);
            while (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                if(t.GetToken() == ERR || t.GetToken() == DONE) {
                    context.RecordError(line, "Unexpected token or EOF while skipping ELSIF block.");
                    return false;
                }
                if (t == IF) nestedIfCount++;
                else if (t == END) {
                    LexItem peek = context.FetchNextLexeme(in, line);
                    if (peek == IF) {
                        if (nestedIfCount > 0) nestedIfCount--;
                        else {
                           context.ReturnLexeme(peek);

                           break;
                        }
                    } else {
                      context.ReturnLexeme(peek);
                    }
                }

                if (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                    t = context.FetchNextLexeme(in, line);
                }
            }

        }


        if (t == ELSE) {
            int nestedIfCount = 0;
            t = context.FetchNextLexeme(in, line);
             while (!((t == END && nestedIfCount == 0))) {
                 if(t.GetToken() == ERR || t.GetToken() == DONE) {
                     context.RecordError(line, "Unexpected token or EOF while skipping ELSE block.");
                     return false;
                 }
                 if (t == IF) nestedIfCount++;
                 else if (t == END) {
                    LexItem peek = context.FetchNextLexeme(in, line);
                    if (peek == IF) {
                        if (nestedIfCount > 0) nestedIfCount--;
                         else {
                           context.ReturnLexeme(peek);

                           break;
                        }
                    } else {
                       context.ReturnLexeme(peek);
                    }
                }

                if (!((t == END && nestedIfCount == 0))) {
                   t = context.FetchNextLexeme(in, line);
                }
            }

        }


    } else {

        int nestedIfCount = 0;
        t = context.FetchNextLexeme(in, line);
        while (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
             if(t.GetToken() == ERR || t.GetToken() == DONE) {
                 context.RecordError(line, "Unexpected token or EOF while skipping IF block.");
                 return false;
             }
            if (t == IF) nestedIfCount++;
            else if (t == END) {
                LexItem peek = context.FetchNextLexeme(in, line);
                if (peek == IF) {
                    if (nestedIfCount > 0) nestedIfCount--;
                    else {
                       context.ReturnLexeme(peek);

                       break;
                    }
                } else {
                   context.ReturnLexeme(peek);
                }
            }

             if (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                t = context.FetchNextLexeme(in, line);
             }
        }


        while (t == ELSIF && !elsifExecuted) {
            Value elsifCondVal;
            if (!CalculateExpressionResult(in, line, elsifCondVal)) return false;
            if (!elsifCondVal.IsBool()) {
                context.RecordError(line, "Run-Time Error-Illegal expression type for elsif condition.");
                return false;
            }

            t = context.FetchNextLexeme(in, line);
            if (t != THEN) {
                context.RecordError(line, "Missing THEN keyword in ELSIF clause.");
                return false;
            }

            if (elsifCondVal.GetBool()) {
                elsifExecuted = true;

                if (!HandleStatementSequence(in, line)) return false;


                 t = context.FetchNextLexeme(in, line);

                 while (t == ELSIF) {
                     Value skipCondVal;
                     if (!CalculateExpressionResult(in, line, skipCondVal)) return false;
                     t = context.FetchNextLexeme(in, line);
                     if (t != THEN) {
                         context.RecordError(line, "Missing THEN keyword in ELSIF clause.");
                         return false;
                     }

                     int nestedIfCount = 0;
                     t = context.FetchNextLexeme(in, line);
                     while (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                         if(t.GetToken() == ERR || t.GetToken() == DONE) {
                             context.RecordError(line, "Unexpected token or EOF while skipping ELSIF block.");
                             return false;
                         }
                         if (t == IF) nestedIfCount++;
                         else if (t == END) {
                             LexItem peek = context.FetchNextLexeme(in, line);
                             if (peek == IF) {
                                 if (nestedIfCount > 0) nestedIfCount--;
                                 else {
                                    context.ReturnLexeme(peek);

                                    break;
                                 }
                             } else {
                                context.ReturnLexeme(peek);
                             }
                         }

                         if (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                            t = context.FetchNextLexeme(in, line);
                         }
                     }
                 }


                 if (t == ELSE) {
                     int nestedIfCount = 0;
                     t = context.FetchNextLexeme(in, line);
                      while (!((t == END && nestedIfCount == 0))) {
                          if(t.GetToken() == ERR || t.GetToken() == DONE) {
                              context.RecordError(line, "Unexpected token or EOF while skipping ELSE block.");
                              return false;
                          }
                          if (t == IF) nestedIfCount++;
                          else if (t == END) {
                             LexItem peek = context.FetchNextLexeme(in, line);
                             if (peek == IF) {
                                 if (nestedIfCount > 0) nestedIfCount--;
                                  else {
                                    context.ReturnLexeme(peek);

                                    break;
                                 }
                             } else {
                                context.ReturnLexeme(peek);
                             }
                         }

                          if (!((t == END && nestedIfCount == 0))) {
                              t = context.FetchNextLexeme(in, line);
                          }
                     }
                 }



            } else {
                nestedIfCount = 0;
                t = context.FetchNextLexeme(in, line);
                while (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                     if(t.GetToken() == ERR || t.GetToken() == DONE) {
                         context.RecordError(line, "Unexpected token or EOF while skipping ELSIF block.");
                         return false;
                     }
                    if (t == IF) nestedIfCount++;
                    else if (t == END) {
                        LexItem peek = context.FetchNextLexeme(in, line);
                        if (peek == IF) {
                             if (nestedIfCount > 0) nestedIfCount--;
                             else {
                                context.ReturnLexeme(peek);

                                break;
                             }
                        } else {
                          context.ReturnLexeme(peek);
                        }
                    }

                    if (!((t == ELSIF || t == ELSE || (t == END && nestedIfCount == 0)))) {
                       t = context.FetchNextLexeme(in, line);
                    }
                }

            }
        }


        if (t == ELSE && !elsifExecuted) {

            if (!HandleStatementSequence(in, line)) return false;
            t = context.FetchNextLexeme(in, line);
        }

    }


    if (t != END) {


        context.RecordError(line, "Missing or misplaced END keyword for IF statement. Found '" + t.GetLexeme() + "' instead.");
        return false;
    }
    t = context.FetchNextLexeme(in, line);
    if (t != IF) {
        context.RecordError(line, "Missing IF keyword after END in IF statement. Found '" + t.GetLexeme() + "' instead.");
        return false;
    }
    t = context.FetchNextLexeme(in, line);
    if (t != SEMICOL) {
        context.RecordError(line, "Missing semicolon at end of IF statement. Found '" + t.GetLexeme() + "' instead.");
        return false;
    }

    return true;
}



bool HandleOutputOperation(istream& in, int& line) {
    LexItem command = context.FetchNextLexeme(in, line);
    bool use_newline = (command == PUTLN);

    LexItem tok = context.FetchNextLexeme(in, line);
    if (tok != LPAREN) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing '(' after " + command.GetLexeme() + " command.");
        return false;
    }

    Value val_to_print;
    if (!CalculateExpressionResult(in, line, val_to_print)) {

        context.RecordError(line, "Failed to evaluate expression within " + command.GetLexeme() + " statement.");
        return false;
    }
     if(val_to_print.IsErr()) {
         context.RecordError(line, "Expression evaluation resulted in an error for " + command.GetLexeme() + " statement.");
         return false;
     }


    cout << val_to_print;
    if (use_newline) {
        cout << endl;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != RPAREN) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing ')' after expression in " + command.GetLexeme() + ".");
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != SEMICOL) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing semicolon after " + command.GetLexeme() + " statement.");
        return false;
    }
    return true;
}


bool HandleInputOperation(istream& in, int& line) {
    LexItem tok = context.FetchNextLexeme(in, line);

    tok = context.FetchNextLexeme(in, line);
    if (tok != LPAREN) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing '(' after GET command.");
        return false;
    }

    LexItem var_tok;

    if (!RetrieveVariableReference(in, line, var_tok)) {
        return false;
    }
    string input_target_var = var_tok.GetLexeme();

    tok = context.FetchNextLexeme(in, line);
    if (tok != RPAREN) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing ')' after variable name in GET.");
        return false;
    }

    tok = context.FetchNextLexeme(in, line);
    if (tok != SEMICOL) {
        context.ReturnLexeme(tok);
        context.RecordError(line, "Missing semicolon after GET statement.");
        return false;
    }


    Token expected_type = context.GetIdentifierType(input_target_var);
    bool read_ok = true;
    Value read_value;

    switch (expected_type) {
        case INT: {
            int v;
            cin >> v;
            if(cin.fail()) read_ok = false;
            else read_value = Value(v);
            break;
        }
        case FLOAT: {
            double v;
            cin >> v;
            if(cin.fail()) read_ok = false;
            else read_value = Value(v);
            break;
        }
        case BOOL: {
            string s;
            cin >> s;
            if(s=="true") read_value = Value(true);
            else if(s=="false") read_value = Value(false);
            else read_ok = false;
            break;
        }
        case STRING: {
            string s;


             cin >> s;

            if(cin.fail()) read_ok = false;
            else read_value = Value(s);
            break;
        }
        case CHAR: {
            char c;
            cin >> c;
            if(cin.fail()) read_ok = false;
            else read_value = Value(c);
            break;
        }
        default:
            read_ok = false;
            context.RecordError(line, "Internal error: Cannot GET input for unknown variable type.");
            break;
    }

    if (!read_ok) {
        cin.clear();

        string dummy; getline(cin, dummy);
        context.RecordError(line, "Run-Time Error-Invalid input received for variable '" + input_target_var + "'.");
        return false;
    } else {

        context.SetIdentifierValue(input_target_var, read_value);
    }
    return true;
}




bool CalculateExpressionResult(istream& in, int& line, Value& result) {

    if (!CalculateLogicalTerm(in, line, result)) return false;

    LexItem op = context.FetchNextLexeme(in, line);
    while (op == AND || op == OR) {
        Value rhs;
        if (!CalculateLogicalTerm(in, line, rhs)) return false;


        if (!result.IsBool() || !rhs.IsBool()) {
            context.RecordError(line, "Run-Time Error-Illegal Operand Type for logical operator.");
            result = Value();
            return false;
        }

        if (op == AND) result = result && rhs;
        else           result = result || rhs;

        op = context.FetchNextLexeme(in, line);
    }
    context.ReturnLexeme(op);
    return !result.IsErr();
}


bool CalculateLogicalTerm(istream& in, int& line, Value& result) {

    if (!CalculateRelationalTerm(in, line, result)) return false;

    LexItem op = context.FetchNextLexeme(in, line);
    if (op == EQ || op == NEQ || op == LTHAN || op == GTHAN || op == LTE || op == GTE) {
        Value rhs;
        if (!CalculateRelationalTerm(in, line, rhs)) return false;



        if (result.GetType() != rhs.GetType() || result.IsErr() || rhs.IsErr()) {


             if ( !((result.IsInt() || result.IsReal()) && (rhs.IsInt() || rhs.IsReal())) && (result.GetType() != rhs.GetType()) )
             {
                 context.RecordError(line, "Run-Time Error-Illegal mixed mode operands for relational operator.");
                 result = Value();
                 return false;
             }
        }



        switch(op.GetToken()) {
            case EQ:    result = (result == rhs); break;
            case NEQ:   result = (result != rhs); break;
            case LTHAN: result = (result < rhs); break;
            case GTHAN: result = (result > rhs); break;
            case LTE:   result = (result <= rhs); break;
            case GTE:   result = (result >= rhs); break;
            default: break;
        }

         if(result.IsErr()) {
             context.RecordError(line, "Runtime error during relational comparison.");
             return false;
         }

    } else {
        context.ReturnLexeme(op);
    }
    return !result.IsErr();
}


bool CalculateRelationalTerm(istream& in, int& line, Value& result) {

    if (!CalculateAdditiveTerm(in, line, result)) return false;

    LexItem op = context.FetchNextLexeme(in, line);
    while (op == PLUS || op == MINUS || op == CONCAT) {
        Value rhs;
        if (!CalculateAdditiveTerm(in, line, rhs)) return false;


        if (op == PLUS) {

            if (!((result.IsInt() && rhs.IsInt()) || (result.IsReal() && rhs.IsReal()))) {
                context.RecordError(line, "Run-Time Error-Illegal operand types for addition.");
                result = Value(); return false;
            }
            result = result + rhs;
        } else if (op == MINUS) {
             if (!((result.IsInt() && rhs.IsInt()) || (result.IsReal() && rhs.IsReal()))) {
                context.RecordError(line, "Run-Time Error-Illegal operand types for subtraction.");
                result = Value(); return false;
            }
            result = result - rhs;
        } else {

            if (!((result.IsString() || result.IsChar()) && (rhs.IsString() || rhs.IsChar()))) {
                context.RecordError(line, "Run-Time Error-Illegal operand types for concatenation.");
                 result = Value(); return false;
            }
            result = result.Concat(rhs);
        }


        if(result.IsErr()) {
             context.RecordError(line, "Runtime error during additive/concatenation operation.");
             return false;
        }

        op = context.FetchNextLexeme(in, line);
    }
    context.ReturnLexeme(op);
    return !result.IsErr();
}


bool CalculateAdditiveTerm(istream& in, int& line, Value& result) {

    LexItem sign_tok = context.FetchNextLexeme(in, line);
    int sign = 0;
    if (sign_tok == PLUS) sign = 1;
    else if (sign_tok == MINUS) sign = -1;
    else context.ReturnLexeme(sign_tok);


    if (!CalculateMultiplicativeTerm(in, line, sign, result)) {
        return false;
    }

    return !result.IsErr();
}


bool CalculateMultiplicativeTerm(istream& in, int& line, int initial_sign, Value& result) {


    if (!CalculateExponentialTerm(in, line, initial_sign, result)) return false;

    LexItem op = context.FetchNextLexeme(in, line);
    while (op == MULT || op == DIV || op == MOD) {
        Value rhs;

        if (!CalculateExponentialTerm(in, line, 0, rhs)) return false;


        if (op == MULT) {
             if (!((result.IsInt() && rhs.IsInt()) || (result.IsReal() && rhs.IsReal()))) {
                 context.RecordError(line, "Run-Time Error-Illegal operand types for multiplication.");
                 result = Value(); return false;
             }
             result = result * rhs;
        } else if (op == DIV) {
             if (!((result.IsInt() && rhs.IsInt()) || (result.IsReal() && rhs.IsReal()))) {
                  context.RecordError(line, "Run-Time Error-Illegal operand types for division.");
                  result = Value(); return false;
             }

             if ((rhs.IsInt() && rhs.GetInt() == 0) || (rhs.IsReal() && rhs.GetReal() == 0.0)) {
                  context.RecordError(line, "Run-Time Error-Illegal Division by Zero.");
                  result = Value(); return false;
             }
             result = result / rhs;
        } else {
             if (!(result.IsInt() && rhs.IsInt())) {
                  context.RecordError(line, "Run-Time Error-Illegal operand types for modulus.");
                  result = Value(); return false;
             }

             if (rhs.GetInt() == 0) {
                  context.RecordError(line, "Run-Time Error-Illegal Modulus by Zero.");
                  result = Value(); return false;
             }
             result = result % rhs;
        }

         if(result.IsErr()) {
              context.RecordError(line, "Runtime error during multiplicative/division/modulus operation.");
              return false;
         }

        op = context.FetchNextLexeme(in, line);
    }
    context.ReturnLexeme(op);
    return !result.IsErr();
}


bool CalculateExponentialTerm(istream& in, int& line, int initial_sign, Value& result) {


    LexItem tok = context.FetchNextLexeme(in, line);

    if (tok == NOT) {
        if (initial_sign != 0) {
            context.RecordError(line, "Unary sign ('+' or '-') cannot precede 'NOT' operator.");
            result = Value(); return false;
        }

        if (!CalculateExponentialTerm(in, line, 0, result)) return false;
        if (!result.IsBool()) {
            context.RecordError(line, "Run-Time Error-Illegal Operand Type for NOT operator.");
            result = Value(); return false;
        }
        result = !result;
    } else {

        context.ReturnLexeme(tok);

        if (!CalculateAtomicValue(in, line, initial_sign, result)) return false;


        LexItem exp_op = context.FetchNextLexeme(in, line);
        if (exp_op == EXP) {
            Value exponent;

            if (!CalculateAdditiveTerm(in, line, exponent)) return false;



             if (result.IsInt()) result = Value(double(result.GetInt()));
            if (!result.IsReal()) {
                context.RecordError(line, "Run-Time Error-Illegal base operand type for exponentiation.");
                result = Value(); return false;
            }

            if(exponent.IsInt()) exponent = Value(double(exponent.GetInt()));
             if(!exponent.IsReal()) {
                 context.RecordError(line, "Run-Time Error-Illegal exponent operand type for exponentiation (must be Int or Real).");
                 result = Value(); return false;
             }


            result = result.Exp(exponent);

            if(result.IsErr()) {
                 context.RecordError(line, "Runtime error during exponentiation operation.");
                 return false;
            }

        } else {
            context.ReturnLexeme(exp_op);
        }
    }
    return !result.IsErr();
}


bool CalculateAtomicValue(istream& in, int& line, int initial_sign, Value& result) {

    LexItem tok = context.FetchNextLexeme(in, line);

    if (tok.GetToken() == ICONST || tok.GetToken() == FCONST || tok.GetToken() == SCONST || tok.GetToken() == BCONST || tok.GetToken() == CCONST) {
        result = MakeValueFromLiteral(tok);

        if (initial_sign == -1) {
            if (result.IsInt()) result = Value(-result.GetInt());
            else if (result.IsReal()) result = Value(-result.GetReal());
            else if (!result.IsErr()) {
                 context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '-').");
                 result = Value(); return false;
            }
        } else if (initial_sign == 1) {
             if (!(result.IsInt() || result.IsReal()) && !result.IsErr()) {
                 context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '+').");
                 result = Value(); return false;
             }
        }
    } else if (tok == IDENT) {
        string name = tok.GetLexeme();

        if (!context.CheckIdentifierDeclared(name)) {
             context.RecordError(line, "Undeclared Variable: " + name);
             result = Value(); return false;
        }
        if (!context.CheckIdentifierInitialized(name)) {
             context.RecordError(line, "Run-Time Error-Uninitialized Variable: " + name);
             result = Value(); return false;
        }

        result = context.GetIdentifierValue(name);


        if (initial_sign == -1) {
            if (result.IsInt()) result = Value(-result.GetInt());
            else if (result.IsReal()) result = Value(-result.GetReal());
            else {
                context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '-') on variable '" + name + "'.");
                result = Value(); return false;
            }
        } else if (initial_sign == 1) {
             if (!(result.IsInt() || result.IsReal())) {
                 context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '+') on variable '" + name + "'.");
                 result = Value(); return false;
             }
        }


        LexItem lparen = context.FetchNextLexeme(in, line);
        if (lparen == LPAREN) {



             Value base_val = context.GetIdentifierValue(name);
             if (!base_val.IsString()) {
                  context.RecordError(line, "Run-Time Error-Indexing a non-string variable.");
                  result = Value(); return false;
             }
             string base_str = base_val.GetString();


            Value idx1, idx2;

            if (!HandleSubscriptRange(in, line, idx1, idx2)) return false;

            LexItem rparen = context.FetchNextLexeme(in, line);
            if (rparen != RPAREN) {
                context.ReturnLexeme(rparen);
                context.RecordError(line, "Missing right parenthesis after string index/range.");
                result = Value(); return false;
            }


            if (idx2.IsErr()) {
                if (!idx1.IsInt()) {
                     context.RecordError(line, "Run-Time Error-Non-integer string index.");
                     result = Value(); return false;
                 }
                int i = idx1.GetInt();
                if (i < 0 || i >= (int)base_str.length()) {
                     context.RecordError(line, "Run-Time Error-String index out of bounds.");
                     result = Value(); return false;
                 }
                result = Value(base_str[i]);
            } else {
                 if (!idx1.IsInt() || !idx2.IsInt()) {
                      context.RecordError(line, "Run-Time Error-Non-integer string range bounds.");
                      result = Value(); return false;
                 }
                 int start = idx1.GetInt();
                 int end = idx2.GetInt();

                 if (start < 0 || start >= (int)base_str.length() || end < 0 || end >= (int)base_str.length()) {
                      context.RecordError(line, "Run-Time Error-String range bounds out of bounds.");
                      result = Value(); return false;
                 }

                 if (start > end) {
                      context.RecordError(line, "Run-Time Error-String range start greater than end.");

                      result = Value(); return false;
                 }

                 result = Value(base_str.substr(start, end - start + 1));
            }

        } else {
            context.ReturnLexeme(lparen);

        }

    } else if (tok == LPAREN) {

        if (!CalculateExpressionResult(in, line, result)) return false;

        LexItem rparen = context.FetchNextLexeme(in, line);
        if (rparen != RPAREN) {
            context.ReturnLexeme(rparen);
            context.RecordError(line, "Missing right parenthesis.");
            result = Value(); return false;
        }


        if (initial_sign == -1) {
            if (result.IsInt()) result = Value(-result.GetInt());
            else if (result.IsReal()) result = Value(-result.GetReal());
            else if (!result.IsErr()) {
                context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '-').");
                result = Value(); return false;
            }
        } else if (initial_sign == 1) {
             if (!(result.IsInt() || result.IsReal()) && !result.IsErr()) {
                  context.RecordError(line, "Run-Time Error-Illegal operand type for sign operator (unary '+').");
                  result = Value(); return false;
             }
        }
    } else {

        context.ReturnLexeme(tok);
        context.RecordError(line, "Invalid primary expression. Found '" + tok.GetLexeme() + "'.");
        result = Value(); return false;
    }
    return !result.IsErr();
}




bool RetrieveVariableReference(istream& in, int& line, LexItem& var_token) {
    var_token = context.FetchNextLexeme(in, line);
    if (var_token != IDENT) {
        context.ReturnLexeme(var_token);
        context.RecordError(line, "Expected a variable identifier here.");
        return false;
    }

    if (!context.CheckIdentifierDeclared(var_token.GetLexeme())) {

        context.RecordError(line, "Undeclared Variable: " + var_token.GetLexeme());
        return false;
    }

    return true;
}


bool HandleSubscriptRange(istream& in, int& line, Value& start_val, Value& end_val) {


    end_val = Value();


    if (!CalculateRelationalTerm(in, line, start_val)) {
        context.RecordError(line, "Invalid expression for string index/range start.");
        return false;
    }
     if (start_val.IsErr()){

         return false;
     }



    LexItem dot1 = context.FetchNextLexeme(in, line);
    if (dot1 == DOT) {
        LexItem dot2 = context.FetchNextLexeme(in, line);
        if (dot2 == DOT) {

            if (!CalculateRelationalTerm(in, line, end_val)) {
                context.RecordError(line, "Invalid expression for string range end.");
                return false;
            }
             if(end_val.IsErr()) {
                 return false;
             }

        } else {

            context.ReturnLexeme(dot2);
            context.ReturnLexeme(dot1);
            context.RecordError(line, "Invalid range operator, expected '..'. Found '.' followed by '" + dot2.GetLexeme() + "'");
            return false;
        }
    } else {

        context.ReturnLexeme(dot1);

    }
    return true;
}
