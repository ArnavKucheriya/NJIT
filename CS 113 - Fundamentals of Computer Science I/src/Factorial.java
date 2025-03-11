import java.util.*;

public class Factorial {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.println("Enter a number: ");
        int num = input.nextInt();

        System.out.println("The factorial of " + num + " is " + factorial(num));

    }

    public static int factorial(int n) {
        if (n == 0) {
            return 1;
        } else if (n < 0) {
            return -1;
        } else {
            int result = 1;
            while (n > 0) {
                result *= n;
                n--;
            }
            return result;
        }
    }
}