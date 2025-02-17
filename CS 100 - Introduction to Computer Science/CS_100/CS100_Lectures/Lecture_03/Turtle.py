# importing Turtle
import turtle
# Creating a screen
screen = turtle.Screen()
# Creating a turtle object(pen)
pen = turtle.Turtle()
# Defining a method to draw a Blue Triangle
def blue_Triangle():
    for i in range(3):
        pen.color("blue")
        pen.forward(100)
        pen.right(120)
blue_Triangle()

# Defining a method to draw a red circle
def centre_Circle():
    for i in range(360):
        # Defining step by step curve motion
        pen.color("red")
        pen.speed(10)
        pen.right(1)
        pen.forward(1)
centre_Circle()

pen.right(90)
pen.forward(125)

turtle.Screen().exitonclick()

