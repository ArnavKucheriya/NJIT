// a_kucheriya_val.cpp
// Implementation of Value Class for SADAL Interpreter
#include "val.h"
#include <iostream>
#include <cmath>
using namespace std;

// Helper function for runtime errors
Value RunTimeErr(const string& errmsg) {
    cerr << "RUNTIME ERROR: " << errmsg << endl;
    return Value(); // Return an error Value
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

