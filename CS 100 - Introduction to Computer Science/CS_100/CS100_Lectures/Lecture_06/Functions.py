# Functions - Lecture 6

# Defining a Function
def my_function():
    print("Hello from a function")
my_function()

'''
def: Function definition keyword
my_function: Function name
(): Arguments (Variable Arguments)
'''

x = 16
def sqrt(x):
    return x**0.5
print(sqrt(x))

# Using Function to Caluclate the Area of a Cirlce from User Input
def area_of_circle(radius):
    return 3.14 * radius**2
radius = float(input("Enter the radius of the circle: "))
print(area_of_circle(radius))

print()

'''
Format of a Function:
def <function_name> (0 or more argumments/parameters):
    <indended body of the <function_name>
    return <argument/parameter>
'''

# Function to calculate the area of a rectangle for user input
length = float(input("Enter the length of the rectangle: "))
width = float(input("Enter the width of the rectangle: "))

def rect_area(length, width):
    return length * width
print(rect_area(length, width))