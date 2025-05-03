#include "val.h"
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <sstream>

using namespace std;

// Addition
Value Value::operator+(const Value& op) const {
    if (IsInt() && op.IsInt())
        return Value(Itemp + op.Itemp);
    if (IsReal() && op.IsReal())
        return Value(Rtemp + op.Rtemp);
    return Value(); // Error
}

// Subtraction
Value Value::operator-(const Value& op) const {
    if (IsInt() && op.IsInt())
        return Value(Itemp - op.Itemp);
    if (IsReal() && op.IsReal())
        return Value(Rtemp - op.Rtemp);
    return Value(); // Error
}

// Multiplication
Value Value::operator*(const Value& op) const {
    if (IsInt() && op.IsInt())
        return Value(Itemp * op.Itemp);
    if (IsReal() && op.IsReal())
        return Value(Rtemp * op.Rtemp);
    // String * Int: repeat string
    if (IsString() && op.IsInt() && op.Itemp >= 0) {
        string res;
        for (int i = 0; i < op.Itemp; ++i)
            res += Stemp;
        return Value(res);
    }
    return Value(); // Error
}

// Division
Value Value::operator/(const Value& op) const {
    if (IsInt() && op.IsInt() && op.Itemp != 0)
        return Value(Itemp / op.Itemp);
    if (IsReal() && op.IsReal() && op.Rtemp != 0.0)
        return Value(Rtemp / op.Rtemp);
    return Value(); // Error (division by zero or bad types)
}

// Modulus
Value Value::operator%(const Value& op) const {
    if (IsInt() && op.IsInt() && op.Itemp != 0)
        return Value(Itemp % op.Itemp);
    return Value(); // Error (bad types or zero)
}

// Equality
Value Value::operator==(const Value& op) const {
    if (T != op.T) return Value(false);
    switch (T) {
        case VINT:    return Value(Itemp == op.Itemp);
        case VREAL:   return Value(Rtemp == op.Rtemp);
        case VSTRING: return Value(Stemp == op.Stemp);
        case VCHAR:   return Value(Ctemp == op.Ctemp);
        case VBOOL:   return Value(Btemp == op.Btemp);
        default:      return Value(); // Error
    }
}

// Inequality
Value Value::operator!=(const Value& op) const {
    if (T != op.T) return Value(true);
    switch (T) {
        case VINT:    return Value(Itemp != op.Itemp);
        case VREAL:   return Value(Rtemp != op.Rtemp);
        case VSTRING: return Value(Stemp != op.Stemp);
        case VCHAR:   return Value(Ctemp != op.Ctemp);
        case VBOOL:   return Value(Btemp != op.Btemp);
        default:      return Value(); // Error
    }
}

// Greater than
Value Value::operator>(const Value& op) const {
    if (T != op.T) return Value(); // Error
    switch (T) {
        case VINT:    return Value(Itemp > op.Itemp);
        case VREAL:   return Value(Rtemp > op.Rtemp);
        case VSTRING: return Value(Stemp > op.Stemp);
        case VCHAR:   return Value(Ctemp > op.Ctemp);
        default:      return Value(); // Error
    }
}

// Less than
Value Value::operator<(const Value& op) const {
    if (T != op.T) return Value(); // Error
    switch (T) {
        case VINT:    return Value(Itemp < op.Itemp);
        case VREAL:   return Value(Rtemp < op.Rtemp);
        case VSTRING: return Value(Stemp < op.Stemp);
        case VCHAR:   return Value(Ctemp < op.Ctemp);
        default:      return Value(); // Error
    }
}

// Less than or equal
Value Value::operator<=(const Value& op) const {
    if (T != op.T) return Value(); // Error
    switch (T) {
        case VINT:    return Value(Itemp <= op.Itemp);
        case VREAL:   return Value(Rtemp <= op.Rtemp);
        case VSTRING: return Value(Stemp <= op.Stemp);
        case VCHAR:   return Value(Ctemp <= op.Ctemp);
        default:      return Value(); // Error
    }
}

// Greater than or equal
Value Value::operator>=(const Value& op) const {
    if (T != op.T) return Value(); // Error
    switch (T) {
        case VINT:    return Value(Itemp >= op.Itemp);
        case VREAL:   return Value(Rtemp >= op.Rtemp);
        case VSTRING: return Value(Stemp >= op.Stemp);
        case VCHAR:   return Value(Ctemp >= op.Ctemp);
        default:      return Value(); // Error
    }
}

// Logical AND
Value Value::operator&&(const Value& op) const {
    if (IsBool() && op.IsBool())
        return Value(Btemp && op.Btemp);
    return Value(); // Error
}

// Logical OR
Value Value::operator||(const Value& op) const {
    if (IsBool() && op.IsBool())
        return Value(Btemp || op.Btemp);
    return Value(); // Error
}

// Logical NOT
Value Value::operator!() const {
    if (IsBool())
        return Value(!Btemp);
    return Value(); // Error
}

// String/char concatenation
Value Value::Concat(const Value& op) const {
    if (IsString() && op.IsString())
        return Value(Stemp + op.Stemp);
    if (IsString() && op.IsChar())
        return Value(Stemp + string(1, op.Ctemp));
    if (IsChar() && op.IsString())
        return Value(string(1, Ctemp) + op.Stemp);
    if (IsChar() && op.IsChar())
        return Value(string(1, Ctemp) + string(1, op.Ctemp));
    return Value(); // Error
}

// Exponentiation (float base only, as per assignment spec)
Value Value::Exp(const Value& op) const {
    if (!IsReal()) return Value(); // Only float base supported
    double base = Rtemp;
    double exponent = 0.0;
    if (op.IsInt()) exponent = op.Itemp;
    else if (op.IsReal()) exponent = op.Rtemp;
    else return Value(); // Error

    // 0^0 or 0^negative is error
    if (base == 0.0 && exponent <= 0.0) return Value();
    // Any^0 = 1
    if (exponent == 0.0) return Value(1.0);
    // Negative exponent
    if (exponent < 0.0) return Value(1.0 / pow(base, -exponent));
    return Value(pow(base, exponent));
}

