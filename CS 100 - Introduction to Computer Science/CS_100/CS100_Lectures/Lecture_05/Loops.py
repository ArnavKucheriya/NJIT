

# For Loop Execution
word = "apple"
for letter in word:
    print(letter)
print()

# For loop in Tuple
days = ('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday')
for day in days:
    print(day)
print()

# For loop in list
number = [1, 2, 3, 4, 5, 6, 7, 8, 9]
for num in number:
    print(num)
print()

'''
Creating an Infinite Loop

# For loop in list with functions

new_number = []
for j in number:
     new_number.append(j)

for i in number:
    number.append(i + 3)
    print('i =', i)
    print('number =', number)
'''

# For loop with Range
for i in range(len(number)):
    print(number[i], end=' ')
print()

# For loops with i in Range
# range(n) generates the sequence 0, ..., n-1
for i in range(5):
    print(i, end=' ')
print()

# For loops with i and n in range
# range(i, n)generates the sequence i, i+1, i+2, ..., n-1
for i in range(3,5):
    print(i, end=' ')
print()

# For loops with i, n, and c in range
# range(i, n, c)generates the sequence i, i+c, i+2c, i+3c, ..., n-1
for i in range(1,6,2):
    print(i, end=' ')
print()
'''
# Exercise
# Write a loop that will print the following sequnces.

a) 0, 1, 2, 3, 4, 5, 6, 7, 8 , 9, 10
b) 1, 2, 3, 4, 5, 6, 7, 8, 9
c) 0, 2, 4, 6, 8
d) 1, 3, 5, 7, 9
e) 20, 30, 40, 50, 60
'''

# Ex a)
for i in range(0,11):
    print(i, end=' ')
print()

# Ex b)
for i in range(1,10):
    print(i, end=' ')
print()

# Ex c)
for i in range(0,9,2):
    print(i, end=' ')
print()

# Ex d)
for i in range(1,10,2):
    print(i, end=' ')
print()

# Ex e)
for i in range(11):
    if i !=10:
        print(str(i)+',', end=' ')
    else:
        print(i)
print()

'''
Different methods of iteration in a sequence.

for letter in s:
    print(letter, end=' ')
print()

for i in range(len(s)):
    print(s[i], end=' ')
print()
'''

lst = [3,6,2,7,4,9,5]

counter = 0
sum_Num = 0
max_Num = lst[0]
min_Num = lst[0]

for num in lst:
    print(num, end=' ')
    counter += 1
    sum_Num += num
    if num >= max_Num:
        max_Num = num
    if num <= min_Num:
        min_Num = num

print()
print("Counter:",counter)
print("Sum:",sum_Num)
print("Max Number:",max_Num)
print("Min Number:",min_Num)
print()

s = "Welcome to the world of Python"
search_letter = 'P'
found_Letter = False

for letter in s:
    if letter == search_letter:
        found_Letter = True
        break
    else:
        found_Letter = False

if found_Letter == True:
    print("Found Letter")
else:
    print("Letter not found")


search_Letter = 'o'
first = True
index_Found = -1

for i in range(len(s)):
    if s[i] == search_Letter and first:
        index_Found = i
        first = False
print("Index of first occurence of letter:",index_Found)


vowel_Count = 0
consonent_Count = 0

for letter in s:
    if letter in 'aeiouAEIOU':
        vowel_Count += 1
    if letter not in 'aeiouAEIOU' and letter != ' ' and letter != '!':
        consonent_Count += 1
print("Number of vowels:",vowel_Count)
print("Number of consonents:",consonent_Count)