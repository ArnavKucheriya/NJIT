'''
Arnav Kucheriya
CS 100 015
HW 04, September 29, 2023
'''
'''
Question 1:
1. Write Python code that does the following:
a. Assigns the values 3, 4 and 5 to the variables a, b and c, respectively.
b. Write an if statement that prints “OK” if a is less than b
c. Write an if statement that prints “OK” if c is less than b
d. Write an if statement that prints “OK” if the sum of a and b is equal to c
e. Write an if statement that prints “OK” if the sum of a squared and b squared equals c squared.
'''
# a.
a, b, c = 3, 4, 5

# b.
if a < b:
    print("OK")

# c.
if c < b:
    print("OK")

# d.
if a + b == c:
    print("OK")

# e.
if a**2 + b**2 == c**2:
    print("OK")

print()

'''
Question 2:
2. Repeat the previous problem with the additional requirement that “NOT OK” is printed if the
condition is false.
'''
# a.
a, b, c = 3, 4, 5

# b.
if a < b:
    print("OK")
else:
    print("NOT OK")

# c.
if c < b:
    print("OK")
else:
    print("NOT OK")

# d.
if a + b == c:
    print("OK")
else:
    print("NOT OK")

# e.
if a**2 + b**2 == c**2:
    print("OK")
else:
    print("NOT OK")

print()

'''
Question 3:
3. Write a program that asks the user for a color, a line width, a line length and a shape. Assume that
the user will specify a shape that is either a line, a triangle, or a square. Use turtle graphics to draw
the shape that the user requests of the size, color, line width and line length that the user requests.
For example, if these are the user choices for color, width, line length and shape, the blue triangle
below would be correct graphical output
what color? blue
what line width? 25
what line length? 100
line, triangle or square? triangle

'''
import turtle

# Input from user
color = input("What color? ")
line_width = int(input("What line width? "))
line_length = int(input("What line length? "))
shape = input("Line, triangle or square? ")

# Set up turtle graphics
window = turtle.Screen()
t = turtle.Turtle()
t.pensize(line_width)
t.color(color)

# Draw the requested shape
if shape.lower() == "line":
    t.forward(line_length)
elif shape.lower() == "triangle":
    for i in range(3):
        t.forward(line_length)
        t.left(120)
elif shape.lower() == "square":
    for i in range(4):
        t.forward(line_length)
        t.left(90)
else:
    print("Invalid shape input. Please choose line, triangle, or square.")

# Close turtle graphics window on click
window.exitonclick()
