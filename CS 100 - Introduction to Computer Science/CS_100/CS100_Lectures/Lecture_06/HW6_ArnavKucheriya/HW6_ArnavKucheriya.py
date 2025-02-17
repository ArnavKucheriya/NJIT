'''
Arnav Kucheriya
CS 100 015
HW 06, October 2, 2023
'''

'''
Question 1:
a. Write a function named hasFinalLetter that takes two parameters
        1. strList, a list of non-empty strings
        2. letters, a string of upper and/or lower case letters
    The function hasFinalLetter should create and return a list of all the strings in strList that end with a letter in letters.
b. Create three test cases, each consisting of a list of non-empty strings and a string of upper 
and/or lower case letters, for your function in Problem 1a. One of these tests should return 
the empty list. For each test case write two assignment statements and a function call that 
pass the test arguments to your function.
'''
def hasFinalLetter(strList, letters):
    '''
    Filters a list of strings to include only those ending with specified letters.

    Args:
    strList (list): A list of non-empty strings.
    letters (str): A string of upper and/or lower case letters.

    Returns:
    list: A list of strings from strList that end with a letter in letters.
    '''
    result = []
    for word in strList:
        if word[-1] in letters:
            result.append(word)
    return result

# Test Cases
test_case_1 = (["apple", "banana", "cherry", "date"], "aeiou")
result_1 = hasFinalLetter(*test_case_1)
print("Test Case 1:", result_1)

test_case_2 = (["hello", "world", "python", "programming"], "xyz")
result_2 = hasFinalLetter(*test_case_2)
print("Test Case 2:", result_2)

test_case_3 = (["dog", "cat", "bird", "fish"], "aeiou")
result_3 = hasFinalLetter(*test_case_3)
print("Test Case 3:", result_3)

'''
Question 2:
a. Write a function named isDivisible that takes two parameters
        1. maxInt, an integer
        2. twoInts, a tuple of two integers
  The function isDivisible should create and return a list of all the ints in the range from 1 to 
maxInt (not including maxInt) that are divisible of both ints in twoInts.
b. Create three test cases, each consisting of a value for maxInt and a value for twoInts, for 
your function in Problem 2a. One of these tests should return the empty list. For each test 
case write two assignment statements and a function call that pass the test arguments to your 
function.
'''

def isDivisible(maxInt, twoInts):
    '''
    Finds integers in the range from 1 to maxInt (exclusive) that are divisible
    by both integers in the twoInts tuple.

    Args:
    maxInt (int): An integer specifying the upper limit of the range.
    twoInts (tuple): A tuple containing two integers.

    Returns:
    list: A list of integers that are divisible by both numbers in twoInts.
    '''
    num1, num2 = twoInts
    result = [i for i in range(1, maxInt) if i % num1 == 0 and i % num2 == 0]
    return result

# Test Cases
test_case_1 = (20, (2, 3))
result_1 = isDivisible(*test_case_1)
print("Test Case 1:", result_1)

test_case_2 = (15, (4, 7))
result_2 = isDivisible(*test_case_2)
print("Test Case 2:", result_2)

test_case_3 = (10, (3, 5))
result_3 = isDivisible(*test_case_3)
print("Test Case 3:", result_3)
