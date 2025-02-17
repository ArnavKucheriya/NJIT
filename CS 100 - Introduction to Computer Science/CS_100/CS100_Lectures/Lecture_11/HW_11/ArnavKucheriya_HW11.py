'''
Arnav Kucheriya
CS 100 015
HW 11, November 28, 2023
'''

class Dog:
    """A class representing a dog.

    Attributes:
        species (str): The species of the dog (class attribute).
        name (str): The name of the dog.
        breed (str): The breed of the dog.
        tricks (list): A list of tricks the dog knows.
    """

    species = 'Canis familiaris'

    def __init__(self, name, breed):
        """Initialize a Dog instance with a name, breed, and an empty list of tricks."""
        self.name = name
        self.breed = breed
        self.tricks = []

    def teach(self, trick):
        """Teach the dog a new trick and print a message."""
        self.tricks.append(trick)
        print(f"{self.name} knows {trick}")

    def knows(self, trick):
        """Check if the dog knows a specific trick, print a message, and return True or False."""
        if trick in self.tricks:
            print(f"Yes, {self.name} knows {trick}")
            return True
        else:
            print(f"No, {self.name} doesn't know {trick}")
            return False

# Test Problem 1
sugar = Dog('Sugar', 'border collie')
print(sugar.name)   # Output: 'Sugar'
print(sugar.breed)  # Output: 'border collie'

# Test Problem 2
print(sugar.tricks)  # Output: []

# Test Problem 3
sugar.teach('frisbee')  # Output: Sugar knows frisbee

# Test Problem 4
print(sugar.knows('frisbee'))  # Output: Yes, Sugar knows frisbee
print(sugar.knows('arithmetic'))  # Output: No, Sugar doesn't know arithmetic

# Test Problem 5
print(Dog.species)  # Output: 'Canis familiaris'
print(sugar.species)  # Output: 'Canis familiaris'
