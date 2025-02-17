
# Creating a TUPLE
pets = ('ant', 'bat', 'cat', 'dog', 'elk')
tple = (0, 1, 'two', 'three', [4, 'five'])
nums = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)

print(pets)
print(tple)
print(nums)
print()

# Operations on Tuples
print('ant' in pets) #True
print('ant' in tple) #False
print()

print(pets + tple)
print()

print(tple[3])
print()

print(min(nums))
print(max(nums))
print(sum(nums))
print()

print(nums[0:5])
print(pets[:3])

# Creating new Lists
p1 = ['do','it','better']
p2 = ['make','us','stronger']

print(p1)
print(p2)  
print()

# Concatination
print(p2[0] + p1[1] + p1[2]) 
print(p2[0] +' ' + p1[1] +' '+ p1[2]) #Using space literal
print()

# Giving multiple arguments to print
# The default behaviour of Print : The commas in a print arguments are read as spaces by the python interpreter.
print(p2[0], p1[1], p1[2])
print()

# Printing List using p3
p3 = p2[0:1] + p1[1:2] + p1[2:]
print(p3)