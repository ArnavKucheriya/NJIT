import random

# Problem 1: Using a `while True` loop with `break` statement
def twoWords(length, firstLetter):
    while True:
        word1 = input(f"Enter a {length}-letter word please: ")
        if len(word1) == length:
            break
    while True:
        word2 = input(f"Enter a word beginning with {firstLetter} please: ")
        if word2[0].lower() == firstLetter.lower():
            break
    return [word1, word2]

# Problem 2: Using `while` without `break` statement
def twoWordsV2(length, firstLetter):
    valid_word1 = False
    valid_word2 = False
    while not valid_word1:
        word1 = input(f"Enter a {length}-letter word please: ")
        if len(word1) == length:
            valid_word1 = True
    while not valid_word2:
        word2 = input(f"Enter a word beginning with {firstLetter} please: ")
        if word2[0].lower() == firstLetter.lower():
            valid_word2 = True
    return [word1, word2]

# Problem 3: Password validation function
def enterNewPassword():
    while True:
        password = input("Enter a password (8-15 characters, including at least one digit): ")
        if 8 <= len(password) <= 15 and any(char.isdigit() for char in password):
            print("Password accepted!")
            break
        else:
            print("Password must be 8-15 characters long and include at least one digit. Try again.")

# Problem 4: GuessNumber game
def guessNumber():
    mystery_number = random.randint(0, 50)
    print("I'm thinking of a number in the range 0-50. You have five tries to guess it.")
    for attempt in range(1, 6):
        guess = int(input(f"Guess {attempt}? "))
        if guess < mystery_number:
            print(f"{guess} is too low")
        elif guess > mystery_number:
            print(f"{guess} is too high")
        else:
            print(f"You are right! I was thinking of {mystery_number}!")
            break
    else:
        print(f"Sorry, you've used all your attempts. The right answer was {mystery_number}.")

if __name__ == "__main__":
    print(twoWords(4, 'B'))
    print(twoWordsV2(4, 'B'))
    enterNewPassword()
    guessNumber()
