Project 1 – Quick Setup & Run Instructions
================================================

Problem 1 – Part 1 (SimpleCracker.java)
--------------------------------------
Required files in one folder:
  - SimpleCracker.java
  - shadow-simple
  - common-passwords.txt

Compile:
  javac SimpleCracker.java

Run:
  java SimpleCracker

Expected output:
  username:password   (for any passwords found)

Problem 1 – Part 2 (Cracker.java)
--------------------------------
Required files in one folder:
  - Cracker.java
  - MD5Shadow.java   (provided by the course)
  - shadow
  - common-passwords.txt

Compile:
  javac MD5Shadow.java Cracker.java

Run:
  java Cracker

Problem 1 – Part 3
------------------
Use a *bigger* wordlist than common-passwords.txt, append the discovered word to common-passwords.txt,
then re-run Cracker.java. In your writeup, include:
  - the password you found
  - the URL/source of the wordlist you used

Problem 2 / 3
-------------
These are written-answer problems. You must do them in a Linux environment with root access.
See the chat response for a command checklist + writeup template.

Notes
-----
- Use Java 11+ (Java 17 recommended).
- Keep files in the same directory unless you modify the code to use explicit paths.
