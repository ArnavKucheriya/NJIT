#ifndef VALUE_H
#define VALUE_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>

using namespace std;

enum ValType { VINT, VREAL, VSTRING, VCHAR, VBOOL, VERR };

class Value {
    ValType	T;
    bool    Btemp;
    int 	Itemp;
	double   Rtemp;
	string	Stemp;
    char 	Ctemp;
    int strcurrLen;
    int strLen;
        
       
public:
    Value() : T(VERR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(bool vb) : T(VBOOL), Btemp(vb), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(int vi) : T(VINT), Btemp(false), Itemp(vi), Rtemp(0.0), Stemp(""), Ctemp(0) {}
    Value(double vr) : T(VREAL), Btemp(false), Itemp(0), Rtemp(vr), Stemp(""), Ctemp(0) {}
    Value(string vs) : T(VSTRING), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(vs), Ctemp(0) { 
		if(vs.length() == 0)
		{
			strcurrLen = 0;
			//strLen should be set by using the SetstrLen() function
		}
		else
		{
			strcurrLen = vs.length();
			strLen = strcurrLen;
		}
	}
    Value(char vs) : T(VCHAR), Btemp(false), Itemp(0), Rtemp(0.0), Stemp(""), Ctemp(vs) { }
    
    
    ValType GetType() const { return T; }
    bool IsErr() const { return T == VERR; }
     bool IsString() const { return T == VSTRING; }
    bool IsReal() const {return T == VREAL;}
    bool IsBool() const {return T == VBOOL;}
    bool IsInt() const { return T == VINT; }
    bool IsChar() const {return T == VCHAR;}
    
    int GetInt() const { if( IsInt() ) return Itemp; throw "RUNTIME ERROR: Value not an Integer"; }
    
    string GetString() const { if( IsString() ) return Stemp; throw "RUNTIME ERROR: Value not a String"; }
    
    double GetReal() const { if( IsReal() ) return Rtemp; throw "RUNTIME ERROR: Value not an Float"; }
    
    bool GetBool() const {if(IsBool()) return Btemp; throw "RUNTIME ERROR: Value not a Boolean";}
    
    char GetChar() const {if(IsChar()) return Ctemp; throw "RUNTIME ERROR: Value not a Character";}
    
    void SetType(ValType type)
    {
    	T = type;
	}
	
	void SetInt(int val)
    {
    	if( IsInt())
    		Itemp = val;
    	else
    		throw "RUNTIME ERROR: Value not an Integer";
	}
	
	void SetReal(double val)
    {
    	if(IsReal() ) 
			Rtemp = val;
		else
			throw "RUNTIME ERROR: Value not an Float";
    	
	}
	
	void SetString(string val)
    {
    	if( IsString() )  
    	{
    		if(val.length() <= strLen)
			{
				Stemp = val;
				strcurrLen = val.length();
			}
			else
			{
				Stemp = val.substr(0, strLen);
			}
		}	
    	else
    		throw "RUNTIME ERROR: Value not a String";
	}
	
	void SetBool(bool val)
    {
    	if(IsBool()) 
    		Btemp = val;
    	else
    		throw "RUNTIME ERROR: Value not a Boolean";
	}
	
	void SetChar(char val)
    {
    	if(IsChar()) 
    		Ctemp = val;
    	else
    		throw "RUNTIME ERROR: Value not a Character";
	}
	
	void SetstrLen(int len)
	{
		if( IsString() )  
    		strLen = len;
    	else
    		throw "RUNTIME ERROR: Value Type not a String";
	}
	
    // numeric overloaded add this to op
    Value operator+(const Value& op) const;
    
    // numeric overloaded subtract op from this
    Value operator-(const Value& op) const;
    
    // numeric overloaded multiply this by op
    Value operator*(const Value& op) const;
    
    // numeric overloaded divide this by oper
    Value operator/(const Value& op) const;
    
    //numeric MOD: overloaded Remainder this by op
    Value operator%(const Value & op) const;
         
    //(Relational = (Equal): overloaded equality operator of this with op
    Value operator==(const Value& op) const;
    
	//Relational /= (Not equal): overloaded inequality operator of this with op
    Value operator!=(const Value& op) const;
    
	//overloaded greater than operator of this with op
	Value operator>(const Value& op) const;
	
	//overloaded less than operator of this with op
	Value operator<(const Value& op) const;
	
	//Relational <= (less than or equal): overloaded less than or equal operator of this with op
	Value operator<=(const Value& op) const;
	
	//Relational >= (Greater than or equal): overloaded Greater than or equal operator of this with op
	Value operator>=(const Value& op) const;
	
	//Logical and: overloaded logical Anding operator of this with op
    Value operator&&(const Value& op) const;
    
	//Logical or: overloaded logical Oring operator of this with op
	Value operator||(const Value& op) const;
	
	//Logical not: overloaded logical Complement operator of this object
	Value operator!(void) const;
	
	//Concatenation &: Concatenate this with op
    Value Concat(const Value & op) const;
    
    //Exponentiation **: raise this to the power of op
    Value Exp(const Value & op) const;
	
    friend ostream& operator<<(ostream& out, const Value& op) {
        if( op.IsInt() ) out << op.Itemp;
        else if(op.IsBool()) out << (op.GetBool()? "true": "false");
        else if( op.IsChar() ) out << op.Ctemp ;
		else if( op.IsString() ) out << op.Stemp ;
        else if( op.IsReal()) out << fixed << showpoint << setprecision(2) << op.Rtemp;
        else if(op.IsErr()) out << "ERROR";
        return out;
    }
};


#endif
