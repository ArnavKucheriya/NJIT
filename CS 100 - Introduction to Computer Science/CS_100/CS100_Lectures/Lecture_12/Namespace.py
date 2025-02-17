'''
Namespaces -> Local and Global
-> The pupose of Functions
-> Global versus Local Namespaces
-> The Program Stack
-> Python's Name Evaluation Rules

The purpose of functions
-> Modularity: They allow us to break down complex problems that require complex programs into small, simple, self->contained pieces. Each small piece can be implemented, tested, and debugged independently.
-> Abstraction: A function has a name that should clearly reflects what it does. That action can then be performed by calling the function by name, abstracting what the function does from how it does it.
-> Reusability: Code that may be used multiple times should be packaged in a function. The code only needs to be written once. And any time that it needs to be modified, extended or debugged, the changes need to be made only once. 
'''

def double(y):
    '''(number) -> number'''
    x = 2
    y *= x
    print('inside double', 'x = ', x, 'y = ', y)
    
x, y = 3, 4
print('outside double', 'x = ', x, 'y = ', y)
double(y)
print('after double', 'x = ', x, 'y = ', y)

'''
Scope and Global vs. Local Namespaces:

-> Every Function has its (Local) own namespace:
    -> This namespace is where names defined during the execution of the function live.
    -> The namespace comes into existence when the function is called, it goes out of existence when the function exits (returns).

-> Every name in python has a scope:
    -> This applies to the name of a variable, function, class, etc.
    -> Outside its scope, the name does not exist, any reference to it will result in an error.
    -> Names created in the interpreter shell or in a module and outside of any function have global scope.
'''

def g(n):
    print('Start g')
    n += 1
    print('n = ', n)
def f(n):
    print('Start f')
    n += 1
    print('n = ', n)
    g(n)
n = 1
print('Outside a function, n = ',n)
f(n)

'''
Java:

public class Main { 
  int x; 
 
  // Constructor with a parameter
  public Main(int a) { 
    this.x = a; 
  } 

  // Call the constructor
  public static void main(String[] args)  { 
    Main myObj = new Main(5); 
    System.out.println("Value of x = " + myObj.x);
  } 
} 

About self in Python:

The reason you need to use self. is because Python does not use the @ syntax to refer to instance attributes. Python decided to do methods in a way that makes the instance to which the method belongs be passed automatically, but not received automatically: the first parameter of methods is the instance the method is called on. That makes methods entirely the same as functions, and leaves the actual name to use up to you (although self is the convention, and people will generally frown at you when you use something else.) self is not special to the code, it's just another object.

Python could have done something else to distinguish normal names from attributes -- special syntax like Ruby has, or requiring declarations like C++ and Java do, or perhaps something yet more different -- but it didn't. Python's all for making things explicit, making it obvious what's what, and although it doesn't do it entirely everywhere, it does do it for instance attributes. That's why assigning to an instance attribute needs to know what instance to assign to, and that's why it needs self..

About this in Java being explained by Oracle:

Within an instance method or a constructor, this is a reference to the current object — the object whose method or constructor is being called. You can refer to any member of the current object from within an instance method or a constructor by using this. The most common reason for using the this keyword is because a field is shadowed by a method or constructor parameter.
'''