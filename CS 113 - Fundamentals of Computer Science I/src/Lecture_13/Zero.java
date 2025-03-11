package Lecture_13;

import java.util.Scanner;

public class Zero {
//-----------------------------------------------------------------
// Deliberately divides by zero to produce an exception.
//-----------------------------------------------------------------
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int numerator = 10;

        System.out.print("Enter the denominator: ");
        int denominator = in.nextInt();

        try {
            System.out.println(numerator / denominator);
        } catch (ArithmeticException exception) {
            System.out.println("This text will not be printed.");
        }
        finally {
            System.out.println("This text will be printed.");
        }
        in.close();
    }

}
