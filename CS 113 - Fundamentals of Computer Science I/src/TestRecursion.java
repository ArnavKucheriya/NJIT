public class TestRecursion {
    public static void main(String[] args) {
        // Question 1
        System.out.println("Problem 1 Test:");
        printDigits(123147);

        // Question 2
        System.out.println("\nProblem 2 Test:");
        int[] a = {1, 3, 2, 5};
        System.out.println(sumArray(a, 3)); // will display 6
        System.out.println(sumArray(a, 4)); // will display 11
    }

    // Problem 1 Implement a recursive method printDigits() that takes an integer num as a parameter and prints its digits, one digit per line.
    public static void printDigits(int num) {
        if (num < 10) {
            System.out.println(num);
        } else {
            printDigits(num / 10);
            System.out.println(num % 10);
        }
    }

    /*
    Problem 2 Implement a recursive method sumArray() that returns the summation of the first count numbers in the array.
    The method takes two parameters:
        - A non-empty integer array, numArray
        - Count, a positive integer representing the number of entries in array to add, no more than size of the array.
     */
    public static int sumArray(int[] numArray, int count) {
        if (count == 1) {
            return numArray[0];
        } else {
            return numArray[count - 1] + sumArray(numArray, count - 1);
        }
    }
}
