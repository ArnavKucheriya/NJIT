'''
Arnav Kucheriya
CS 100 015
HW 05, October 5, 2023
'''

'''
Question 1:
Create a list named months of the months of the year. Write a for loop that iterates over the 
elements of months and prints out each one that begins with letter 'J', one month per line.
'''
# Creating a list of months
months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"]

# Printing months that start with the letter 'J'
for month in months:
    if month.startswith('J'):
        print(month)

'''
Question 2:
Write a for loop that iterates over all of the integers in the range 0 through 99, inclusive, and prints 
out all of those numbers that are divisible by both 2 and 5
'''
# Printing numbers between 0 and 99 that are divisible by both 2 and 5
for num in range(100):
    if num % 2 == 0 and num % 5 == 0:
        print(num)

'''
Qustion 3:
Consider the strings created by these assignment statements:
horton = "A person's a person, no matter how small."
vowels = "aeiouAEIOU"
Write a for loop that prints out all the vowels in horton in the order they appear in horton.

'''
# Strings
horton = "A person's a person, no matter how small."
vowels = "aeiouAEIOU"

# Printing vowels in horton in the order they appear
for char in horton:
    if char in vowels:
        print(char)
