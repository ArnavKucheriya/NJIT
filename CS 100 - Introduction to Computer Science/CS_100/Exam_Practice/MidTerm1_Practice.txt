# CS 100 Midterm 1 Practice Exam 

# Question 1
a = 3
b = 3
c = 1
print(c+(b-c)*a)

# Question 2
a = 14
b = 3.0
c = a//b
print(c)

# Question 3
a = 14
b = 4
c = a%b
print(c)

# Question 4
import math
r = 4
c = math.sqrt(r)
print(c)

# Question 5
a = 4
b = 3
c = 4
d = b == c and a > b
print(d)

# Question 6
a = 4
b = 3
c = 4
d = b == c or a > b
print(d)

# Question 7
a = 'tree'
b = 'truck'
c = a < b
print(c)

# Question 8
a = 'tree'
b = 'truck'
c = len(a) < len(b)
print(c)

# Question 9
a = 'for'
b = 'forest'
c = a in b
print(c)

# Question 10
a = ['f','o','r']
b = ['for','f','o','r','e','s','t']
c = a in b
print(c)

# Question 11
a = 'apple'
b = 'banana'
c = b[0] + a[-1] * 2 + a[2]
print(c)

# Question 12
books = ('math', 'physics', 'chemistry', 'history')
# books[1] = 'english'
# print(books)
print("Error, Tuples are immutable")

# Question 13
books = ['math', 'physics', 'chemistry', 'history']
books[1] = 'english'
print(books)

# Question 14
books = ['math', 'physics', 'chemistry', 'history']
c = len(books) - len(books[0])
print(c)

# Question 15
books = ['math', 'physics', 'chemistry', 'history']
c = books.count('math') + books.index('math')
print(c)

# Question 16
books = ['math', 'physics', 'chemistry', 'history']
books.append('math')
c = books.count('math') - books.index('math')
print(c)

# Question 17
a = ['one', 'in', 'a', 'million']
b = ['time', 'flies', 'swiftly']
c = b[0]
print(c)

# Question 18

a = ['one', 'in', 'a', 'million']
b = ['time', 'flies', 'swiftly']
c = b[0:1] + a[0:0]
print(c)

# Question 19
import math

a = 3
b = 4
c = math.sqrt(a**2+b**2)
print(c * 5.0)

# Question 20
name = input('Enter your name: ')
age = input('Enter your age: ')
print(name + ', you will be ' + (age + 1) + ' next year.')

# Question 21
name = input('Enter your name: ')
age = int(input('Enter your age: '))
print(name + ', you will be ' + (age + 1) + ' next year.')

# Question 22
name = input('Enter your name: ')
age = input('Enter your age: ')
print(name + ', you will be ' + (age + str(1)) + ' next year.')

# Question 23
score = int(input("Enter your score: "))
if score >= 70:
    print("You passed.")
elif score >= 80:
    print("You did well.")
elif score >= 90:
    print("Excellent!")
else:
    print("Did not compute.")

# Question 24
score = int(input("Enter your score: "))
if score >= 90:
    print("Excellent!")
elif score >= 80:
    print("You did well.")
elif score >= 70:
    print("You passed.")
else:
    print("Did not compute.")

# Question 25
temp = 35
snow = True

if temp > 32 and not snow:
    print('stay inside now')
elif temp > 35 or not snow:
    print('go outside now')
elif temp < 32 and snow:
    print('stay inside')
else:
    print('go outside')

# Question 26
lst = ['M','a','r','c','h']
s = ''
for letter in lst:
    s += letter
print(s)

# Question 27
lst = ['M','a','r','c','h']
lst2 = []

for letter in lst:
    lst2.append(letter)

print(lst2[2:2])

# Question 28
lst = ['M','a','y']
lst2 = []

for letter in lst:
    lst2.append(letter)

print(lst2*2)
      
# Question 29
lst = ['M','a','r','c','h']
vowels = 'aeiouAEIOU'
c = []

for letter in lst:
    if letter in vowels:
        c.append(letter)

print(c)

# Question 30
lst = ['M','a','r','c','h']
vowels = 'aeiouAEIOU'
c = ''

for letter in lst:
    if letter not in vowels:
        c += letter

print(c)

# Question 31
lst = ['M','a','r','c','h']
vowels = 'aeiouAEIOU'
c = ()

for letter in lst:
    if letter not in vowels:
        c += letter

print(c)

# Question 32
lst = ('M','a','r','c','h')
vowels = 'aeiouAEIOU'
c = []

for letter in lst:
    if letter in vowels:
        c.append(letter)

print(c)

# Question 33
s = "welcome"

for i in range(1,4,1):
    print(s[i], end='')

# Question 34
s = "welcome"

for i in range(1,4,2):
    print(s[i], end='')

# Question 35
score = 80

if score >= 80 and < 100:
    print("You did well!")
else:
    print("You did not do well.")

# Question 36
score = 80

if score > 80 and score <= 100:
    print("You did well!")
else:
    print("You did not do well.")

# Question 37
numList = [4, 3, 1, -2]
result = 0
for i in numList:
    if i%2 == 1:
        result += 1
print(result)

# Question 38
def isOdd(num):
    if num%2 == 0:
        return True
    else:
        return False

age = 23
print(isOdd(age))

# Question 39
def evenCount(seq):
    counter = 0
    for elem in seq:
        if elem%2 == 0:
            counter += 1
            return counter

nums = [4, 1, 2, 8, 7, 4]
print(evenCount(nums))

# Question 40
def evenCount(seq):
    counter = 0
    for elem in seq:
        if elem%2 == 0:
            counter += 1
    return counter

nums = [4, 1, 2, 8, 7, 4]
print(evenCount(nums))

'''
Question 41

Given the problem: Write a for loop that iterates over all of the integers in the range 0 through 99, inclusive, and stores in a list all of the numbers that are evenly divisible by both 2 and 5. Print the count of such numbers and the list of such numbers. The code is started below but you must fill in the five blanks.

counter = 0
lst = []
for num in range(
 ):
    if 
 == 0 and 
 == 0:
        counter 

        
                         
print(counter)
print(lst)
'''

'''
Question 42

The code below is supposed to iterate through the given list and return the largest value in the list. If correct, it should print 87. The code is started below but you must fill in the five blanks.

 

myList = [5, 22, 87, 41, 72]
largestSoFar = -1
for num in 
 :
    if 
 > 
 :
        
 = 

print(largestSoFar)
'''

'''
Question 43

The code below is supposed to define a function that counts the number of odd numbers in a given sequence of numbers.  When the function is called with the given argument the output should be 3. Fill in the blanks.

 

def countOdd(myLst):
    counter = 

    for num in 
 :
        if num%2 != 
 :
            counter += 

    return 

theList = [6, 3, 5, 4, 1, 6]
print(countOdd(theList))
'''

'''
Question 44

The code below is supposed to define a function that counts the number of words that end in a letter that is a consonant. When the function is called with the given argument the output should be 4. Fill in the blanks.

 

def countEndsWithConsonant(
 ):
    counter = 0
    vowels = '
 '
    for word in sequence:
        if word[
 ] not in vowels:
            counter += 

    return 

tup = ('there', 'are', 'not', 'way', 'too', 'many', 'words')
print(countEndsWithConsonant(tup))
'''

# END OF PRACTICE EXAM 1.