file_String = "C:\\Users\\Arnav\\Documents\\NJIT_CS\\CS_100\\CS100_Lectures\\Lecture_9\\Input_File.txt"
'''
new_file = open(file_String, "r")
print(new_file.read())
new_file.close()

# Path: CS_100/CS100_Lectures/Lecture_9/Files.py

new_file = open(file_String, "r+")
new_file.write("This is a new line")
print(new_file.read())
new_file.close()
'''

file_List = ["New line 1", "New line 2", "New line 3"]
new_file = open(file_String, "r+")
for line in file_List:
    new_file.write(line + "\n")
new_file.close()

new_file = open(file_String, "r+")
print(new_file.read())
new_file.close()

