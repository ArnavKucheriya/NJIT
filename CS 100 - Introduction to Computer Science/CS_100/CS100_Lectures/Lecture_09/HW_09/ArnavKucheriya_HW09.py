'''
Problem 1
Write a function file_copy that takes two string parameters (in_file and out_file) and copies the 
content of in_file into out_file. Assume that in_file exists before file_copy is called. For 
example, the following would be correct input and output:
>>> file_copy('created_equal.txt', 'copy.txt')
>>> copy_f = open('copy.txt')
>>> copy_f.read()
'We hold these truths to be self-evident,\nthat all men are created equal\n'
Problem 2
Write a function named file_stats that takes one string parameter (in_file) that is the name of an 
existing text file. The function file_stats should calculate three statistics about in_file: the number 
of lines it contains, the number of words and the number of characters, and print the three statistics on 
separate lines. For example, the following would be correct input and output:
>>> file_stats('created_equal.txt')
lines 2
words 13
characters 72
Note: The number of characters may vary slightly between operating systems. Similarly, the number of lines 
may vary by 1 line, depending on the method used to calculate it.
Problem 3
Write a function named repeat_words that takes two string parameters:
1. in_file: the name of an input file that exists before repeat_words is called
2. out_file: the name of an output file that repeat_words creates
Assume that the input file is in the current working directory and write the output file to that directory.
For each line of the input file, the function repeat_words should write to the output file all of the words 
that appear more than once on that line. Each word should be lower cased and stripped of leading and 
trailing punctuation. Each repeated word on a line should be written to the corresponding line of the 
output file only once, regardless of the number of times the word is repeated.
For example, if the following is the content of the file catInTheHat.txt:
Too wet to go out and too cold to play ball.
So we sat in the house.
We did nothing at all.
So all we could do was to Sit! Sit! Sit! Sit!
The following function call:
inF = 'catInTheHat.txt'
outF = 'catRepWords.txt'
repeat_words(inF, outF)
should create the file catRepWords.txt with the content:
too to
sit
'''
def file_copy(in_file, out_file):
    with open(in_file, 'r') as source_file:
        content = source_file.read()
    with open(out_file, 'w') as target_file:
        target_file.write(content)

# Example usage
file_copy('created_equal.txt', 'copy.txt')

def file_stats(in_file):
    with open(in_file, 'r') as file:
        lines = file.readlines()
        num_lines = len(lines)
        num_words = sum(len(line.split()) for line in lines)
        num_chars = sum(len(line) for line in lines)
    print(f'lines {num_lines}')
    print(f'words {num_words}')
    print(f'characters {num_chars}')

# Example usage
file_stats('created_equal.txt')

import os
import re

def repeat_words(in_file, out_file):
    with open(in_file, 'r') as source_file:
        lines = source_file.readlines()

    repeated_words = []
    for line in lines:
        words = re.findall(r'\b\w+\b', line.lower())
        unique_words = set(words)
        for word in unique_words:
            if words.count(word) > 1:
                repeated_words.append(word)

    with open(out_file, 'w') as target_file:
        target_file.write(' '.join(repeated_words))

# Example usage
inF = "C:\\Users\\Arnav\\OneDrive\\Desktop\\GitHub\\NJIT_CS\\CS_100\\CS100_Lectures\\Lecture_09\\HW_09\\created_equal.txt"
outF = 'C:/Users/Arnav/OneDrive/Desktop/GitHub/NJIT_CS/CS_100/CS100_Lectures/Lecture_09/HW_09/catRepWords.txt'
repeat_words(inF, outF)

print(os.getcwd())
