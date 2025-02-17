# Objects and Classes
a = 3
b = 3.0
c = 'three'
d = [1,2,3]

# Printing the dataypes of each variable
print(a, type(a))
print(b, type(b))
print(c, type(c))
print(d, type(d))
print()

a = 2**1024
print(a)
print()

# Overflow Errors: Any numeric value that is too large to be represented in memory will get an overflow error.
# b = 2.0**1024
# print(b)
# print()

a = +3
b = -3
print(a+b)
print(a-b)
print()

# Object COnstructors
num = 3.99999
print(num)
print(int(num))
print()

str1 = '3.99999'
print(str1)
print(float(str1))
print(int(float(str1)))
print()

num1 = int('3')
num2 = int(3.99999)
print(num1, num2)
print()

print(str(34.5))