/**
 * @author Arnav Kucheriya
 */

import java.util.*;

public class RandomPlate {
    public static void main(String[] args) {
        // Generate random letters
        String letters = generateRandomLetters(5);

        // Generate random digits
        String digits = generateRandomDigits(2);

        // Combine letters and digits to form the plate number
        String plateNumber = letters + digits;

        // Display the generated plate number
        System.out.println("Random Plate Number: " + plateNumber);
    }

    // Method to generate random uppercase letters
    private static String generateRandomLetters(int count) {
        Random random = new Random();
        StringBuilder letters = new StringBuilder();

        for (int i = 0; i < count; i++) {
            char randomLetter = (char) (random.nextInt(26) + 'A');
            letters.append(randomLetter);
        }

        return letters.toString();
    }

    // Method to generate random digits
    private static String generateRandomDigits(int count) {
        Random random = new Random();
        StringBuilder digits = new StringBuilder();

        for (int i = 0; i < count; i++) {
            int randomDigit = random.nextInt(10);
            digits.append(randomDigit);
        }

        return digits.toString();
    }
}
