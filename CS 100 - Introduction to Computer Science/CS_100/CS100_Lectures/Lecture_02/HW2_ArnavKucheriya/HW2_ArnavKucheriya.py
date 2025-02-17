'''
Arnav Kucheriya
CS 100 Section 015
HW 02, September 16, 2023
'''
'''
QUESTION 1: 

This question practices the use of a list method. Assign to the variable grades a list of 10 letter grades from among 'A', 'B', 'C', 'D', and 'F'. For example:

grades = ['A', 'F', 'C', 'F', 'A', 'B', 'A', 'C', 'A', 'B']

Write a Python expression that creates a list named frequency, in which the elements are the number of times each of the letters A, B, C, D and F appear in grades. For example, for the above value of grades, the following would be correct output:

frequency = [4, 2, 2, 0, 2]

Your expression must give the correct values for any list of grades, not just the one in your list. Hint: use the list method count. 
'''
# Creating a List called Grades.
grades = ['A', 'F', 'A', 'F', 'C', 'F', 'A', 'B', 'A', 'C']
print("List of Letter Grades: ",grades)
print("Total Letter Grades: ",len(grades))
print()

# Counting the Frequency of each letter grade.
count_A = grades.count('A')
count_B = grades.count('B')
count_C = grades.count('C')
count_D = grades.count('D')
count_F = grades.count('F')

# Creating a List that holds the Frequency of each letter Grade from the List grade
frequency = [count_A, count_B, count_C, count_D, count_F]
print("Frequency of each Letter Grade: ",frequency)

'''
QUESTION 2:

This question practices list membership, list indexes and list slices.

a. Write a Python statement that creates a list named dog_breeds that contains the elements 'collie', 'sheepdog', 'Chow', and 'Chihuahua' in the order given.
b. Write a Python statement that uses list slicing to create a list herding_dogs that is made up of the first two elements of dog_breeds.
c. Write a Python statement that uses list indexing to create a list tiny_dogs that is made up of the last element of dog_breeds.
d. Write a Python statement that tests whether 'Persian' is in the list dog_breeds and prints either True or False depending on the answer.
'''
#2a:
# Creating a List called dog_breeds.
dog_breeds = ['collie', 'sheepdog', 'Chow', 'Chihuahua']
print("List of Dog Breeds: ",dog_breeds)
print()
#2b:
# Slicing the list dog_breeds to create a new list called herding_dogs.
herding_dogs = dog_breeds[0:2]
print("List of Herding Dogs: ",herding_dogs)
print()

#2c:
# Indexing the list dog_breeds to create a new list called tiny_dogs.
tiny_dogs = dog_breeds[-1]
print("List of Tiny Dogs: ",tiny_dogs)
print()

#2d:
# Checking whether 'Persian' is in the list dog_breeds.
# 'Persian' in dog_breeds
print("Is Persian in the list dog_breeds? ", 'Persian' in dog_breeds)