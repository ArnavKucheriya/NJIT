#include <iostream>
#include <string>
#include <vector> 
using namespace std; 
#include "val.h"
#include "val.cpp"


void ExecuteMult(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " * " << val2 << " is " <<  val1 * val2 << endl;
}

void ExecuteLThanE(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " <= " << val2 << " is " <<  (val1 <= val2) << endl;
}

void ExecuteExp(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " ** " << val2 << " is " <<  (val1.Exp( val2)) << endl;
}

void ExecuteConcat(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " & " << val2 << " is " <<  (val1.Concat(val2)) << endl; 
}


	
int main(int argc, char *argv[])
{
	Value ErrorVal;
	double num1 = 9.25;
	Value doubleVal1(num1);
	double num2 = 4;
	Value doubleVal2(num2);
	string str1 = "CS280";
	Value StrVal1(str1); 
	string str2 = "Fall 2024";
	Value StrVal2(str2);
	
	int intval1 = 18;
	Value intVal1(intval1);
	int intval2 = 6;
	Value intVal2(intval2);
	char ch1 = 'S';
	Value chVal1(ch1);
	char ch2 = 'z';
	Value chVal2(ch2);
	bool b1 = true;
	Value bVal1(b1);
	bool b2 = false;
	Value bVal2(b2);
	
	vector<Value> vals( {ErrorVal, intVal1, intVal2, doubleVal1, doubleVal2, StrVal1, StrVal2, chVal1, chVal2, bVal1, bVal2} );
	bool multflag = false, LThanEflag = false, expflag = false, catflag = false;
	
	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}
	
	string arg( argv[1] );
	if( arg == "-mul" )
		multflag = true;
	else if( arg == "-lte" )
		LThanEflag = true;
	else if( arg == "-exp" )
		expflag = true;		
	else if( arg == "-cat" )
		catflag = true;
	
	else {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
	}
		
	
	cout << "ErrorVal=" << ErrorVal << endl; 
	//cout << "IntVal=" << IntVal << endl; 
	cout << "intVal1=" << intVal1 << endl; 
	cout << "intVal2=" << intVal2 << endl;
	cout << "doubleVal1=" << doubleVal1 << endl; 
	cout << "doubleVal2=" << doubleVal2 << endl;
	cout << "StrVal1=" << StrVal1 << endl; 
	cout << "StrVal2=" <<  StrVal2 << endl;
	cout << "chVal1=" << chVal1 << endl;
	cout << "chVal2=" << chVal2 << endl;
	
	if(multflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
			for( int j = 0; j < vals.size(); j++ )
				if( i != j )
					ExecuteMult( vals[i], vals[j] );
	}
	
	if(LThanEflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteLThanE( vals[i], vals[j] );
	}	
	
	if(expflag)
	{				
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteExp( vals[i], vals[j] );
	}
	if(catflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteConcat( vals[i], vals[j] );
	}
	
	
	return 0;
}

