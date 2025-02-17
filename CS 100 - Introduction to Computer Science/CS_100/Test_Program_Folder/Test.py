import numpy as np

msg = 'hello world, this is a test Python Program file.'
print(msg)

a = 10
b = 5
print('Value of a + b = ', a + b)

a = 'Changing the value of a to a String'
print(a)

print('Rolling a Dice!')
# Random Number Generator using Numpy (Pip installing numpy)
print(np.random.randint(1,9))
print()

msg = 'hello world'
print(msg.capitalize())
print(msg.split('e'))
print()

# Adding a orray to the program
array = np.array([1,2,3,4,5,6,7,8,9,10])

#Printing the array
print(array)

#Performing different operations on the array
print(array[0])
print(array[1:5])
print(array[5:])
print(array[:5])
print(array[-1])

print()

for i in array:
    print(i)

print()

array2 = np.array([[1,2,3,4,5,6,7,8,9,10],[11,12,13,14,15,16,17,18,19,20]])
print(array2)

print()

N = 5
arr = [0 for i in range(N)]
print(arr)
print()

#Creating 2D List using Naive Method
rows, cols = (5, 5)
arr = [[0]*cols]*rows
print(arr)

rows, cols = (5, 5)
arr = [[0]*cols]*rows
print(arr, "before")

arr[0][0] = 1 # update only one element
print(arr, "after")
print()

#Creating 1D List using List Comprehension
rows, cols = (5, 5)
arr = [[0 for i in range(cols)] for j in range(rows)]
print(arr)
print()

#Creating 1D List using Empty List
arr=[]
rows, cols=5,5
for i in range(rows):
	col = []
	for j in range(cols):
		col.append(0)
	arr.append(col)
print(arr)
print()

#Initializing 2D Array
# Python 3 program to demonstrate working
# of method 1 and method 2.
rows, cols = (5, 5)
# method 2 1st approach
arr = [[0]*cols]*rows
# lets change the first element of the
# first row to 1 and print the array
arr[0][0] = 1

for row in arr:
	print(row)

# method 2 2nd approach
arr = [[0 for i in range(cols)] for j in range(rows)]

# again in this new array lets change
# the first element of the first row
# to 1 and print the array
arr[0][0] = 1
for row in arr:
	print(row)
print()

rows, cols = (5, 5)

# method 2 2nd approach
arr = [[0 for i in range(cols)] for j in range(rows)]

# check if arr[0] and arr[1] refer to
# the same object
print(arr[0] is arr[1]) # prints False

# method 2 1st approach
arr = [[0]*cols]*rows

# check if arr[0] and arr[1] refer to the same object prints True because there is only one
#list object being created.
print(arr[0] is arr[1])


   