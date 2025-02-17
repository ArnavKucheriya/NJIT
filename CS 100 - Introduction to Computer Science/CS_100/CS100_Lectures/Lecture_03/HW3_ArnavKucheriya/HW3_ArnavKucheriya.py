'''
Arnav Kucheriya
CS 100 Secttion 015
HW 03, September 23, 2023
'''
import math
import turtle
'''
========================================================================================================================
'''
# Q1: Write a code that uses turtle graphics to draw an euilateral triangle, a square, and a regular pentagon, each with a side lenght 100.

# Function to draw an equilateral triangle
def draw_triangle(side_length):
    for _ in range(3):
        turtle.forward(side_length)
        turtle.left(120)

# Function to draw a square
def draw_square(side_length):
    for _ in range(4):
        turtle.forward(side_length)
        turtle.left(90)

# Function to draw a regular pentagon
def draw_pentagon(side_length):
    for _ in range(5):
        turtle.forward(side_length)
        turtle.left(72)

# Set up the Turtle environment
turtle.speed(1)  # Adjust the drawing speed if needed

# Draw the shapes
side_length = 100

turtle.penup()
turtle.goto(-150, 0)  # Position the turtle at the starting point

turtle.pendown()
draw_triangle(side_length)

turtle.penup()
turtle.forward(200)  # Move to the next position

turtle.pendown()
draw_square(side_length)

turtle.penup()
turtle.forward(200)  # Move to the next position

turtle.pendown()
draw_pentagon(side_length)
'''
========================================================================================================================
'''
# Q2: Write a code that uses turtle graphics to draw four concentric circles of radius 50, 100, 150, and 200.

# Function to draw a circle with a given radius
def draw_circle(radius):
    turtle.circle(radius)

# Set up the Turtle environment
turtle.speed(1)  # Adjust the drawing speed if needed

# Draw the concentric circles
radii = [50, 100, 150, 200]

for radius in radii:
    turtle.penup()
    turtle.goto(0, -radius)  # Position the turtle at the center of the circle
    turtle.pendown()
    draw_circle(radius)


# Close the drawing window when clicked
# turtle.exitonclick()

'''
========================================================================================================================
'''

# Q3: Write code that uses the Python math module to compute and print out the values of
# a. 100!
# b. the log (base 2) of 1,000,000
# c. the greatest common divisor of 63 and 49

# Calculate and print 100!
factorial_100 = math.factorial(100)
print(f"a. 100! = {factorial_100}")

# Calculate and print the log (base 2) of 1,000,000
log_base_2 = math.log2(1000000)
print(f"b. log2(1,000,000) = {log_base_2}")

# Calculate and print the greatest common divisor of 63 and 49
gcd_63_49 = math.gcd(63, 49)
print(f"c. GCD of 63 and 49 = {gcd_63_49}")