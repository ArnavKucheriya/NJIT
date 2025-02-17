'''
Arnav Kucheriya
CS 100 015
HW 01, September 11, 2023
'''
import math

#Exercise 5b
int1 = 12
int2 = 3
int3 = 5

print(int1, int2, int3)

#Exercise 5c
float1_Terminating = 12.0
float2_Recurring = 3.333333
float3_Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286

print(float1_Terminating, float2_Recurring, float3_Pi)

#Exercise 5d
string1 = "Hello World!"
string2 = "This is assignment 1 - Homework 1"
string3 = "I am a student at New Jersey Institute of Technology"

print(string1, string2, string3)
print()
#Testing Indexing of String Characters
#length = 'length'
#print(length[len(length)-1])

'''
====================================================================================================
#Exercise 6 [1.1]

Q1. In a print statement, what happens if you leave out one of the parentheses, or both?
A1. If you leave out one or both parentheses in a print statement, you'll get a syntax error. Python requires the use of parentheses to define the arguments you want to print.

Q2. If you are trying to print a string, what happens if you leave out one of the quotation marks, or both?
A2. If you leave out one or both quotation marks when trying to print a string, you'll also get a syntax error. Quotation marks are used to define the beginning and end of a string in Python.

Q3. You can use a minus sign to make a negative number like -2. What happens if you put a plus sign before a number? What about 2++2?
A3. If you put a plus sign before a number, it doesn't change the number's value. So, +2 is the same as 2. In the case of 2++2, it will be interpreted as 2 + (+2), which is equal to 4.

====================================================================================================
'''
'''
#Exercise 6 [1.2]

Q1. How many seconds are there in 42 minutes 42 seconds?
A1. There are 42 minutes * 60 seconds/minute + 42 seconds = 2562 seconds.

Q2. How many miles are there in 10 kilometers? Hint: there are 1.61 kilometers in a mile.
A2. To convert kilometers to miles, you can divide the number of kilometers by the conversion factor (1.61). So, 10 kilometers / 1.61 kilometers/mile ≈ 6.21 miles.

Q3. If you run a 10-kilometer race in 42 minutes 42 seconds, what is your average pace (time per mile in minutes and seconds)? What is your average speed in miles per hour?
A3. To find the average pace per mile, first, convert the race time to minutes: 42 minutes + (42 seconds / 60) minutes ≈ 42.7 minutes. Then, divide this time by the distance in miles (6.21 miles) to get the average pace per mile.

Average Pace per Mile ≈ 42.7 minutes / 6.21 miles ≈ 6.88 minutes per mile.

To find the average speed in miles per hour, divide the total distance (6.21 miles) by the total time (42.7 minutes) converted to hours:

Average Speed ≈ 6.21 miles / (42.7 minutes / 60) hours ≈ 8.73 miles per hour.
'''

# Exercise 6 [1.2]
# Q1. How many seconds are there in 42 minutes 42 seconds?
seconds = (42 * 60) + 42
print("There are",seconds,"seconds in 42 minutes 42 seconds.")
print()

# Q2. How many miles are there in 10 kilometers? Hint: there are 1.61 kilometers in a mile.
miles = 10 / 1.61
print("There are",miles,"miles in 10 kilometers.")
print()

# Q3. If you run a 10-kilometer race in 42 minutes 42 seconds, what is your average pace (time per mile in minutes and seconds)? What is your average speed in miles per hour?
hours = (((42) + (42/60))/60)
miles = 10 / 1.61
speed = miles / hours
print("Your average speed is",speed,"miles per hour.")
print()

'''
====================================================================================================
#Exercise 6 [2.1]

Q. Repeating my advice from the previous chapter, whenever you learn a new feature, you should try it out in interactive mode and make errors on purpose to see what goes wrong.

• We've seen that n = 42 is legal. What about 42 = n?
A. 42 = n will result in a syntax error. In Python, you can't assign a value to a constant like 42.

• How about x = y = 1?
A. x = y = 1 is legal in Python and assigns the value 1 to both x and y.

• In some languages, every statement ends with a semi-colon, ;. What happens if you put a semi-colon at the end of a Python statement?
A. Python does not require or use semicolons to terminate statements. Adding a semicolon at the end of a Python statement is allowed but unnecessary.

• What if you put a period at the end of a statement?
A. Putting a period at the end of a statement will result in a syntax error. Periods are not used to terminate statements in Python.

• In math notation, you can multiply x and y like this: xy. What happens if you try that in Python?
A. In Python, you need to use the * operator to multiply variables. So, xy is not valid. You should use x * y to multiply x and y.

====================================================================================================
'''
'''
#Exercise 6 [2.2]

Q1. The volume of a sphere with radius r is (4/3) πr^3. What is the volume of a sphere with radius 5?
A1. To calculate the volume of a sphere with radius 5, use the formula:

Volume = (4/3) * π * (5^3) = (4/3) * π * 125 ≈ 523.6 cubic units.

Q2. Suppose the cover price of a book is $24.95, but bookstores get a 40% discount. Shipping costs $3 for the first copy and 75 cents for each additional copy. What is the total cost of 60 copies?
A2. To calculate the total cost for 60 copies:

Calculate the discount price of one book: $24.95 - ($24.95 * 0.40) = $14.97
Calculate the cost of 60 copies at the discounted price: 60 * $14.97 = $898.20
Add the shipping cost: $3 (for the first copy) + $0.75 (for each of the remaining 59 copies) = $3 + $44.25 = $47.25
Add the cost of the books and shipping: $898.20 + $47.25 = $945.45
So, the total cost of 60 copies is $945.45.

Q3. If I leave my house at 6:52 am and run 1 mile at an easy pace (8:15 per mile), then 3 miles
A3. To calculate your arrival time after running 4 miles:

Calculate the total time for running 4 miles: 4 miles * 8 minutes 15 seconds/mile = 33 minutes.
Add this time to your starting time: 6:52 am + 33 minutes = 7:25 am.
So, you will arrive at your destination at 7:25 am.

====================================================================================================
'''
# Exercise 6 [2.2]
# Q1. The volume of a sphere with radius r is (4/3) πr^3. What is the volume of a sphere with radius 5?
radius = 5
volume = (4/3) * math.pi * (radius**3)
print("The volume of a sphere with radius",radius,"is",volume,"cubic units.")
print()

# Q2. Suppose the cover price of a book is $24.95, but bookstores get a 40% discount. Shipping costs $3 for the first copy and 75 cents for each additional copy. What is the total cost of 60 copies?
discount_price = 24.95 - (24.95 * 0.40)
cost_of_60_copies = 60 * discount_price
shipping_cost = 3 + (0.75 * 59)
total_cost = cost_of_60_copies + shipping_cost
print("The total cost of 60 copies is $",total_cost)
print()

# Q3. If I leave my house at 6:52 am and run 1 mile at an easy pace (8:15 per mile), then 3 miles
start_time = 6 + (52/60)
easy_pace = (8 + (15/60)) / 60
total_time = start_time + (easy_pace * 4)
print("You will arrive at your destination at",total_time,"AM.")
print()
