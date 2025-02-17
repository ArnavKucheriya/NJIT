package Labs;
// ************************************************************
// Count.java
//
// This program reads in strings (phrases) and counts the
// number of blank characters and certain other letters
// in the phrase.
// ************************************************************

import java.util.Scanner;

public class CountingCharacter {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);

        String phrase; // a string of characters
        int countBlank; // the number of blanks (spaces) in the phrase
        int length; // the length of the phrase
        char ch; // an individual character in the string

// Print a program header
        System.out.println();
        System.out.println("Character Counter");
        System.out.println();

/*        // Read in a string and find its length
        System.out.print("Enter a sentence or phrase: ");
        phrase = scan.nextLine();
        length = phrase.length();
        */


        boolean b;
        do {
            System.out.println("Please enter a valid phrase, enter 0 to exit: ");
            phrase = scan.nextLine();
            length = phrase.length();

            b = !phrase.equals("0");

            countBlank = 0;

            int count_a = 0, count_A = 0;
            int count_e = 0, count_E = 0;

            for (int i = 0; i < length; i++) {
                ch = phrase.charAt(i);
                switch (ch) {
                    case ' ':
                        countBlank++;
                        break;
                    case 'a':
                        count_a++;
                        break;
                    case 'e':
                        count_e++;
                        break;
                    case 'A':
                        count_A++;
                        break;
                    case 'E':
                        count_E++;
                        break;
                }
            }

            System.out.println();
            System.out.println("Number of blank spaces: " + countBlank);
            System.out.println("Number of A's: " + count_A);
            System.out.println("Number of a's: " + count_a);
            System.out.println("Number of E's: " + count_E);
            System.out.println("Number of e's: " + count_e);
            System.out.println();

        } while (b == true);
    }
}
