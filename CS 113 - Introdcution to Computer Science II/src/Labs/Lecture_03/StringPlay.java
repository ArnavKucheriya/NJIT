package Labs.Lecture_03;

import java.util.Scanner;

// **************************************************
// StringPlay.java
// Author : Arnav Kucheriya
// Play with String objects
// **************************************************
public class StringPlay
{
    public static void main (String[] args)
    {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter a College Name: ");
        String college = input.nextLine();
        System.out.print("Enter a Town: ");
        String town = input.nextLine();

        /*String college = new String ("PoDunk College");
        String town = "Anytown USA"; // part (a)*/
        int stringLength;
        String change1, change2, change3;
        stringLength = college.length(); // part (b)
        System.out.println (college + " contains " + stringLength + " characters.");
        change1 = college.toUpperCase(); // part (c)
        change2 = change1.replace("O", "*"); // part (d)
        change3 = college.concat(town); // part (e)
        System.out.println ("The final string is " + change3);
    }
}