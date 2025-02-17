/*
// @Author: Arnav Kucheriya
// Homework 06 - TestArrays.java
 */

import java.util.Random;
public class TestArrays {

    // Method to count occurrences of each number in the range 0-5 from 100 random integers
    public static int[] numberFreq() {
        int[] frequencies = new int[6];
        Random rand = new Random();

        for (int i = 0; i < 100; i++) {
            int num = rand.nextInt(6);
            frequencies[num]++;
        }

        return frequencies;
    }

    // Method to generate the first 'total' Fibonacci numbers
    public static int[] fibo(int total) {
        int[] fibonacci = new int[total];
        fibonacci[0] = 1;
        fibonacci[1] = 1;

        for (int i = 2; i < total; i++) {
            fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
        }

        return fibonacci;
    }

    // Method to count the number of odd face values after rolling dice
    public static int oddDice(Die[] dice) {
        int oddCount = 0;

        for (Die die : dice) {
            die.roll();
            int result = die.getFaceValue();
            if (result % 2 != 0) {
                oddCount++;
            }
        }

        return oddCount;
    }

    public static void main(String[] args) {
        // Test numberFreq()
        int[] freq = numberFreq();
        System.out.println("Frequency of each number in range 0-5:");
        for (int i = 0; i < freq.length; i++) {
            System.out.println(i + ": " + freq[i]);
        }

        // Test fibo()
        int totalFibonacci = 10;
        int[] fibonacciSequence = fibo(totalFibonacci);
        System.out.println("\nFirst " + totalFibonacci + " Fibonacci numbers:");
        for (int num : fibonacciSequence) {
            System.out.print(num + " ");
        }

        // Test oddDice()
        Die[] dice = { new Die(6), new Die(6), new Die(6) }; // Creating 3 dice
        int oddCount = oddDice(dice);
        System.out.println("\n\nNumber of dice landing on odd face value: " + oddCount);
    }
}