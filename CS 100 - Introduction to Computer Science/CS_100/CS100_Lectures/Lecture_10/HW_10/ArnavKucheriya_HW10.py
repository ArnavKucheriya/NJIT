'''
Arnav Kucheriya
Homework 10
CS 100 Section 15
11/8/2023
'''

'''
Problem 1
Write a function named initialLetterCount that takes one parameter, wordList — a list of words. 
Create and return a dictionary in which each initial letter of a word in wordList is a key and the 
corresponding value is the number of words in wordList that begin with that letter. The keys in the 
dictionary should be case-sensitive, which means 'a' and 'A' are two different keys.
For example, the following is correct output:
horton = ['I', 'say', 'what', 'I', 'mean', 'and', 'I', 'mean', 'what', 'I', 
'say']
print(initialLetterCount(horton))
{'I': 4, 's': 2, 'w': 2, 'm': 2, 'a': 1}
'''
def initialLetterCount(wordList):
    letter_count = {}
    for word in wordList:
        initial_letter = word[0]
        letter_count[initial_letter] = letter_count.get(initial_letter, 0) + 1
    return letter_count

horton = ['I', 'say', 'what', 'I', 'mean', 'and', 'I', 'mean', 'what', 'I', 'say']
print(initialLetterCount(horton))

'''
Problem 2
Write a function named initialLetters that takes one parameter, wordList – a list of words. Create 
and return a dictionary in which each initial letter of a word in wordList is a key and the corresponding 
value is a list of the words in wordList that begin with that letter. There should be no duplicate words in 
any value in the dictionary.
For example, the following is correct output:
print(initialLetters(horton))
{'I': ['I'], 's': ['say'], 'w': ['what'], 'm': ['mean'], 'a': ['and']}
'''
def initialLetters(wordList):
    initial_letter_dict = {}
    for word in wordList:
        initial_letter = word[0]
        if initial_letter in initial_letter_dict:
            if word not in initial_letter_dict[initial_letter]:
                initial_letter_dict[initial_letter].append(word)
        else:
            initial_letter_dict[initial_letter] = [word]
    return initial_letter_dict

print(initialLetters(horton))

'''
Problem 3
Write a function named shareOneLetter that takes one parameter, wordList – a list of words. Create 
and return a dictionary in which each word in wordList is a key and the corresponding value is a list of 
all the words in wordList that share at least one letter with that word. There should be no duplicate 
words in any value in the dictionary.
For example, the following is correct output:
print(shareOneLetter(horton))
{'I': ['I'], 'say': ['say', 'what', 'mean', 'and'], 'what': ['say', 'what', 
'mean', 'and'], 'mean': ['say', 'what', 'mean', 'and'], 'and': ['say', 'what', 
'mean', 'and']}
'''
def shareOneLetter(wordList):
    shared_letter_dict = {}
    for word1 in wordList:
        shared_words = []
        for word2 in wordList:
            if word1 != word2 and any(letter in word2 for letter in word1):
                shared_words.append(word2)
        shared_letter_dict[word1] = shared_words
    return shared_letter_dict

print(shareOneLetter(horton))
