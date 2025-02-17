'''
While loops:
    > Iterate over each element in a sequence
        for elem in sequence:
            # do something
             
    > Loop a fixed number of times
        for i in range(num):
            # do something

    > Loop until a condition is met
        while condition:
            # do something
            # update condition
            # break; To exit the Loop
'''

def get_Negetive_Number():
    '''
    This function will ask the user to input a Negative number until the user inputs a negetive number.
    '''
    num = int(input("Enter a Negative number: "))
    while num >= 0:
        print("You entered a positive number.")
        num = int(input("Enter a Negative number: "))
    return num

# print(get_Negetive_Number())

def get_Odd_Number():
    '''
    This function will ask the user to input a Odd  number until the user inputs a Odd number.
    '''
    num = int(input("Enter a Odd number: "))
    while num%2 == 0:
        print("You entered a Even number.")
        num = int(input("Enter a Odd number: "))
    return num

# print(get_Odd_Number())

# infinite Loop patterns
def infinite_loop():
    '''
    This function will print infinite loop.
    '''
    while True:
        name = input("What is your name? ")
        print('Hello {}'.format(name))

# infinite_loop()

def cities():
    lst = []
    while True:
        city = input("Enter the name of a city: ")
        if city == '':
            return lst
            # The return fumction acts as the breaker for the While loop. However it can only be used when the While loop exists inside of an function.
        lst.append(city)

# print(cities())

table =[[2,3,0,6],[0,3,4,5],[4,5,6,0]]

def all(t):
    for row in t:
        for num in row:
            print(num, end=' ')
        print()

all(table)