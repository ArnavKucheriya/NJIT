# New file for Lecture 6: Functions (Defining, Calling, and Returning)

def average_Value_2_Numbers(val1, val2):
    return (val1 + val2) / 2
print(average_Value_2_Numbers(2, 4))

def absolute_Value(val):
    if val < 0:
        return -val
    else: 
        return val
print(absolute_Value(-4))

def even_or_Odd(val):
    if val % 2 == 0:
        return "Even"
    else:
        return "Odd"
print(even_or_Odd(3))

def max_Value_List(num_List):
    largest_Num = num_List[0]
    for num in num_List:
        if num > largest_Num:
            largest_Num = num
    return largest_Num
print(max_Value_List([9, 3, 5, 2, 1, 7, 8, 4, 6]))

def length_List(num_List):
    counter = 0
    for num in num_List:
        counter += 1
    return counter
print(length_List([9, 3, 5, 2, 1, 7, 8, 4, 6]))

def sum_List(num_List):
    sum = 0 
    for num in num_List:
        sum += num
    return sum
print(sum_List([9, 3, 5, 2, 1, 7, 8, 4, 6]))

def average_List(num_List):
    return sum_List(num_List) / length_List(num_List)
print(average_List([9, 3, 5, 2, 1, 7, 8, 4, 6]))

def welcome_Function(name):
    return "Hello " + name + ". Welcome to the World of Python!"
print(welcome_Function(input("Enter your name: ")))

def count_Odd_Numbers(num_List):
    counter = 0
    for num in num_List:
        if num % 2 != 0:
            counter += 1  
    return counter
def count_Even_Numbers(num_List):
    counter = 0
    for num in num_List:
        if num % 2 == 0:
            counter += 1  
    return counter
print(count_Odd_Numbers([1, 2, 3, 4, 5, 6, 7, 8, 9]))
print(count_Even_Numbers([1, 2, 3, 4, 5, 6, 7, 8, 9]))
