// *****************************************************************
// Power.java
//
// Reads in two integers and uses a recursive power method
// to compute the first raised to the second power.
// *****************************************************************

import java.util.Scanner;

public class Power {
    public static void main(String[] args) {
        int base, exp;
        int answer;
        Scanner scan = new Scanner(System.in);
        System.out.print("Welcome to the power program! ");
        System.out.println("Please use integers only.");
//get base
        System.out.print("Enter the base you would like raised to a power: ");
        base = scan.nextInt();
//get exponent
        System.out.print("Enter the power you would like it raised to: ");
        exp = scan.nextInt();
        answer = power(base, exp);
        System.out.println(base + " raised to the " + exp + " is " + answer);
    }

    // ----------------------------------------------
// Computes and returns base^exp
// ----------------------------------------------
    public static int power(int base, int exp) {
        int pow;
        // Base case: if the exponent is 0, set pow to 1
        if (exp == 0) {
            pow = 1;
        }
        // Recursive case: compute base^exp using recursion
        else {
            pow = base * power(base, exp - 1);
        }
        // Return the result
        return pow;
    }
}