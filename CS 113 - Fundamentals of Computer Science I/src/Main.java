import java.util.Arrays;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("Hello! Give me a String and choose a function to execute!");
        System.out.println("Functions: \n 1. Reverse String \n 2. Concatenate String");

        System.out.print("String: ");
        String str = input.nextLine();

        System.out.print("Function: ");
        int func = input.nextInt();

        switch (func){
            case 1 -> {

                System.out.println("Reversed String");
            }

            case 2 -> {
                System.out.print("Enter another String to concatenate: ");
                String conc = input.next();

                str = str + conc;

                System.out.println("Concatenated String: " + str);
            }


                default -> throw new IllegalStateException("Unexpected value: " + func);
        }

    }
}
