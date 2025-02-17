import math

# math.sqrt(x) returns the square root of x
print(math.sqrt(4)) # 2.0
# math.pow(x,y) returns x raised to the power y
print(math.pow(2,3)) # 8.0
# math.ceil(x) returns the smallest integer greater than or equal to x
print(math.ceil(4.2)) # 5
# math.floor(x) returns the largest integer less than or equal to x
print(math.floor(4.2)) # 4
print()
# math.pi returns the value of pi
print(math.pi) # 3.141592653589793
print()

# Exercise
c = math.sqrt(3**2 + 4**2)
print(c)
print()

# Area and Circumference of a circle
r = 10
area = math.pi * r**2
circumference = 2 * math.pi * r
print(area)
print(circumference)
print()

"""
The value of the Boolean
expression that checks whether a
point with coordinates (5, 5) is
inside a circle with center (0,0) and
radius 7.
"""
# Point (5,5) has Side a = 5 units and side b = 5 units from the x and y axis respectively.
radius = 7
