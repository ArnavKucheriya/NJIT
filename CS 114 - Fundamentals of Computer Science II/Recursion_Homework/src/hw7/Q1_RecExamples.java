package hw7;

public class Q1_RecExamples {
    
    // Question X263: Largest in array
    public int largest(int[] numbers, int index) {
        if (index == 0) { // Base case
            return numbers[0];
        }
        return Math.max(numbers[index], largest(numbers, index - 1)); // Recursive case
    }

    // Question X264: Multiply two numbers
    public int multiply(int x, int y) {
        if (x == 0) { // Base case
            return 0;
        } else {
            return multiply(x - 1, y) + y; // Recursive case
        }
    }

    // Question X265: GCD (Greatest Common Divisor)
    public int GCD(int x, int y) {
        if (y == 0) { // Base case
            return x;
        } else {
            return GCD(y, x % y); // Recursive case
        }
    }

    // Question X266: Logarithm
    public int log(int b, int n) {
        if (n < b) { // Base case
            return 0;
        } else {
            return 1 + log(b, n / b); // Recursive case
        }
    }

    // Question X267: Sum of numbers from 1 to k
    public int sumToK(int k) {
        if (k <= 0) { // Base case
            return 0;
        } else {
            return k + sumToK(k - 1); // Recursive case
        }
    }

    // Question X268: Sum of odd numbers up to n
    public int addOdd(int n) {
        if (n <= 0) { // Base case
            return 0;
        }
        if (n % 2 != 0) { // Odd value
            return n + addOdd(n - 1); // Recursive case
        } else { // Even value
            return addOdd(n - 1); // Recursive call skipping even number
        }
    }

    // Question X269: Sum of digits in a number
    public int sumOfDigits(int number) {
        if (number < 10) { // Base case
            return number;
        }
        return number % 10 + sumOfDigits(number / 10); // Recursive case
    }

    // Question X270: Count occurrences of 'A' in a string
    public int countChr(String str) {
        if (str.length() == 0) { // Base case
            return 0;
        }
        int count = 0;
        if (str.substring(0, 1).equals("A")) { // Check for 'A'
            count = 1;
        }
        return count + countChr(str.substring(1)); // Recursive case
    }
}

