'''
Binary Numbers:
100 = -4
101 = -3
110 = -2
111 = -1
000 = 0
001 = 1
010 = 2
011 = 3
100 = 4
101 = 5
110 = 6
111 = 7

0101 = 1*2^0 + 0*2^1 + 1*2^2 + 0*2^3 = 1 + 0 + 4 + 0 = 5
1010 = 0*2^0 + 1*2^1 + 0*2^2 + 1*2^3 = 0 + 2 + 0 + 8 = 10

-6%2 = 0
-5%2 = 1
-4%2 = 0
-3%2 = 1
-2%2 = 0
-1%2 = 1
0%2 = 0
1%2 = 1
2%2 = 0
3%2 = 1
4%2 = 0
5%2 = 1
6%2 = 0

-6%3 = 0
-5%3 = 1
-4%3 = 2
-3%3 = 0
-2%3 = 1
-1%3 = 2
0%3 = 0
1%3 = 1
2%3 = 2
3%3 = 0
4%3 = 1
5%3 = 2
6%3 = 0
'''

#Defining Lists
list_Pets = ['Dog', 'Cat', 'Bird', 'Fish', 'Hamster', 'Snake', 'Lizard', 'Turtle', 'Rabbit', 'Frog']
list_Nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

# Printing Lists
print(list_Pets)
print(list_Nums)
print()

# Length of a list
print('Length of List Pets:',len(list_Pets))
print('Length of List Nums:',len(list_Nums))
print()

# Min and Max of List
print('Min of List Pets:',min(list_Pets))
print('Max of List Pets:',max(list_Pets))
print('Min of List Nums:',min(list_Nums))
print('Max of List Nums:',max(list_Nums))
print()

# Sum of List
print('Sum of List Nums:',sum(list_Nums))
print()

print('Dog' in list_Pets) #True
print('Dog' in list_Nums) #False
print('Hammer' in list_Pets) #False

print(2 in list_Pets) #False
print(2 in list_Nums) #True
print(2324 in list_Nums) #False
print()

#Concatenation
print('Concatenation:',list_Nums + list_Pets)
print()
print(5*list_Nums)
print()
print(2*list_Pets)
print()

# Accessing elements in a list
print('Printing Index 0 of List Pets:',list_Pets[0])
print('Printing Index 6 of List Pets:',list_Pets[6])
print()

# Accessing elements in a list using negative indices
print('Printing the last value of List Pets:',list_Pets[-1])
print('Printing the second to last value of List Pets:',list_Pets[-2])
print()

# Slicing a list
print('Printing the first 3 values of List Pets:',list_Pets[:3])
print('Printing the last 3 values of List Pets:',list_Pets[-3:])
print()

# Slicing a list with a step
print('Printing every 2nd value of List Pets:',list_Pets[::2])
print()

# Slicing a list with a negative step
print('Printing every 2nd value of List Pets in reverse:',list_Pets[::-2])
print()

# Mutating Lists
list_Pets[0] = 'Parrot'
list_Pets[-1] = 'Pig'
print('Mutated List Pets:',list_Pets)
print('Mutated List Pets in reverse:',list_Pets[::-1])
print()

List_New_Pets = ['Monkey', 'Panda', 'Fox']
print('List New Pets:',List_New_Pets)
print()

# Appending to a list
List_New_Pets.append('Pig')
print('Appending List New Pets:', List_New_Pets)
print()

List_New_Pets.append('200')

print('Appending List New Pets with Integer:', List_New_Pets)
print()

# Counting the number of times an element appears in a list
List_New_Pets.append('Panda')
print('Counting the Number of Times Pig appears:  ',List_New_Pets.count('Pig'))
print('Counting the Number of Times Panda appears:',List_New_Pets.count('Panda'))
print()

# Indexing an element in a list
print(List_New_Pets)
print('Indexing Pig:',List_New_Pets.index('Pig'))
print('Indexing Panda:',List_New_Pets.index('Panda')) #Returns the index of the element at first match.
print()

# Removing the last element from a list
print(List_New_Pets)
print('Last Element Added:',List_New_Pets.pop())
print('List New Pets after pop:',List_New_Pets)
print()

# Removing a specific element from a list
print(List_New_Pets)
List_New_Pets.remove('Pig')
print('List New Pets after remove:',List_New_Pets)
print()

# Reversing a list
List_New_Pets.reverse()
print('List New Pets after reverse:',List_New_Pets)
print()

# Sorting a List accoding to Increasing Order
List_New_Pets.remove('200')
List_New_Pets.sort()
print('List New Pets after sort:',List_New_Pets)
print()

# Sorting a List accoding to Decreasing Order
List_New_Pets.sort(reverse=True)
print('List New Pets after reverse sort:',List_New_Pets)
print()

# Creating a new Number List
List_New_Nums = list_Nums
print('List New Nums:',List_New_Nums)
print()

# Shallow Copy
List_New_Nums = list_Nums[:]
print('List New Nums Shallow Copy:',List_New_Nums)
print()

# Deep Copy
List_New_Nums = list_Nums.copy()
print('List New Nums Deep Copy:',List_New_Nums)
print()

# Taking the Mean of a list
print(List_New_Nums)
print('Mean of List Nums:',sum(list_Nums)/len(list_Nums))
print()

# Taking the Median of a list
List_New_Nums.append(11)
print(List_New_Nums)
List_New_Nums.sort()
print('Median of List Nums:',List_New_Nums[len(List_New_Nums)//2])
List_New_Nums.pop()
print()

# Taking the Mode of a list
List_New_Nums.append(10)
List_New_Nums.append(10)
List_New_Nums.append(10)
List_New_Nums.append(10)
List_New_Nums.append(10)
List_New_Nums.append(10)
print(List_New_Nums)
print('Mode of List Nums:',max(set(List_New_Nums), key = List_New_Nums.count))
print()
