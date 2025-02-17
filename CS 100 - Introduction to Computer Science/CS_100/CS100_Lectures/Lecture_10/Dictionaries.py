# Dictionaries are Associative Arrays (Data Types   Key:Value)
# Dictionaries are defined using curly braces '{}'
from operator import itemgetter
from typing import ItemsView


definitions = {'modest':'unassuming', 'eat':'chew and swallow'}
bdays = {'Napoleon':'15 Aug 1769', 'Lady Gaga':'Mar 28 1986'}
species = {'Fido':'dog', 'Finny':'catfish', 'Pepe Le Pew':'skunk'}
# Dictionaries are mutable, unordered, and indexed.
print(definitions['modest'])
print(bdays['Lady Gaga'])
print(species)
print()

# Basic Operations using Dictionaries:
# Creating an empty dictionary:
dict_Empty = {}
print(dict_Empty)
# Adding a key:value pair, using index and assignment operators
dict_Empty['YWCC'] = 'YWCC'
# Finding the value of key using the index operator
dict_Empty['YWCC']
print(dict_Empty)
# Using get() method to find the value of a key
print(dict_Empty.get('YWCC'))
# Finding the length of a dictionary
print(len(dict_Empty))
# Assigning a new value to an existing key
dict_Empty['YWCC'] = 'Ying Wu College of Computing'
print(dict_Empty)
# Removing a key:Value pair and return its value
pop_Key = dict_Empty.pop('YWCC')
print(pop_Key)
print(dict_Empty)
print()

# Adding new Key:Value pairs to the dictionary
dict_Empty = {'YWCC':'Ying Wu College of Computing', 'NWE':'Newark College of Engineering'}
print(dict_Empty)
# Finding the size of the dictionary
print(len(dict_Empty))
# Testing for membership (Presence of a Key)
print('YWCC' in dict_Empty)
# Incorporating another dictionary into the current dictionary
dict_New = {'CSLA':'College of Science and Liberal Arts', 'MTSM':'Martin Tuchman School of Management'}
dict_Empty.update(dict_New)
print(dict_Empty)
print(dict_New)
print()

# Iterating over a dictionary
dict_Name = {'Tree':'Oak', 'Flower':'Rose', 'Fruit':'Apple'}
for key in dict_Name:
    print(key)
print()
for key in dict_Name:
    print(dict_Name[key])
print()

# Iterating over a dictionary with conditional statements
# Iterating over Keys of dictionary
for key in dict_Name.keys():
    if 'e' in key:
        print(key)
print()

# Iterating over Values of dictionary
for value in dict_Name.values():
    if 'e' in value:
        print(value)
print()

for value in dict_Name.values():
    if 'e' in value:
        print(value)
        

# Iterating over Key:Value pairs of dictionary
for key, value in dict_Name.items():
    if 'e' in key:
        print(key, value)
print()

# Adding 100,000 values to a dictionary
dict_100K = {}
for i in range(100000):
    dict_100K[i] = i
# print(dict_100K)

def frequency(itemList):
    '''Compute the frequency of each item in
      itemList. Return the result as a dictionary 
      in which each distinct item in itemList is a
      key and the item's frequency (count) is the 
      associated value.'''
    counters = {}
    for item in itemList:
          # if the item hasn't been seen before
        if item not in counters:
              # add the item to the dictionary 
              # and set its count to 1
              counters[item] = 1
          # otherwise, increment the count of item
    else:
        counters[ItemsView] += 1
    return counters